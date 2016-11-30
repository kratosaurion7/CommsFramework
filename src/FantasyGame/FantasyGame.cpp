#include "FantasyGame.h"

#include <cassert>

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <Spritesheet.h>
#include <DrawObject.h>
#include <BaseSprite.h>
#include <BaseText.h>
#include <Vectors.h>
#include <XmlReader.h>
#include <Spritesheet.h>
#include <FRectangle.h>
#include <FSize.h>
#include <XDirectory.h>
#include <XFile.h>
#include <ConfigurationManager.h>
#include <TgaFile.h>
#include <QuickWindow.h>
#include <PathLoader.h>
#include <Viewport.h>

#include "ProgDef.h"
#include "World.h"
#include "Map.h"
#include "Tile.h"
#include "MapXmlStructs.h"

#include "Player.h"
#include "PlayerCamera.h"
#include "CheatMenu.h"

FantasyGame* _gameInstance; // Fuck it
FantasyGame * GetGameInstance()
{
    return _gameInstance;
}

FantasyGame::FantasyGame()
{
    _gameInstance = this;

    Engine = new GameEngine();

    Settings = Engine->ConfigManager;
}

FantasyGame::~FantasyGame()
{
    Engine->DetachActor(MainCamera);
    Engine->DetachActor(GamePlayer);

    delete(MainCamera);
    delete(GamePlayer);
}

void FantasyGame::Init()
{
    ReadCoreSettings();

	char* rootAssetPath = Settings->Get("assets_root", "assets\\");
    PathLoader::SetBasePath(rootAssetPath);

    // Init the engine first, this gives access to the services proposed by the engine
    InitEngine();

    // Next we can init the game world, we can't fully create the tiles yet
    // because the graphics are not loaded yet.
    World* root = World::CreateWorldFromXml("World.xml");
    this->GameWorld = root;

    // Now that we have a World to load, we can check and load the assets that are needed
    InitGraphics();

    // Finally, we init the game. Player, camera, etc. After that, the game is ready to play.
    InitGame();
}


void FantasyGame::ReadCoreSettings()
{
    // TODO : Find a way to copy the config file from somewhere else than the assets

    Settings->LoadConfig();

	scaleFactor = Settings->GetFloat("game_scale_factor", 4);
	tileSize = Settings->GetFloat("game_tile_size", 16);
	scaledSize = tileSize * scaleFactor;
}

void FantasyGame::InitEngine()
{
    int width = Settings->GetInt("window_width", 640);
    int height = Settings->GetInt("window_height", 640);
    Engine->Init(width, height);

    createdWindows = new BaseList<int>();

    DebugCheatsMenu = new CheatMenu();
    Engine->AttachActor(DebugCheatsMenu);

    TileIndexIdentifiers = new PointerList<BaseText*>();
}

void FantasyGame::InitGraphics()
{
    // Find all settings named Spritesheet
    auto pred = [](std::string p) {
        return p == "Spritesheet";
    };

    auto spritesheetValues = Settings->GetWhere(pred);
    auto it = ITBEGIN(spritesheetValues);
    while (it != ITEND(spritesheetValues))
    {
        char* spritesheetPath = *it;

        Spritesheet* ssheet = new Spritesheet(spritesheetPath, this->Engine->Graphics);

        Engine->Graphics->AddSpritesheet(ssheet);

        it++;
    }

    PointerList<Map*>* maps = this->GameWorld->Maps;
    auto mapIt = ITBEGIN(maps);
    while (mapIt != ITEND(maps))
    {
        Map* mapToLoad = *mapIt;

        for (int i = 0; i < mapToLoad->Height; i++)
        {
            for (int j = 0; j < mapToLoad->Width; j++)
            {
                Tile* tileToLoad = mapToLoad->Tiles[i][j];

                tileToLoad->TileSprite = this->Engine->CreateSprite();
                tileToLoad->TileSprite->Show(true);
                tileToLoad->TileSprite->SetScale(scaleFactor);
                tileToLoad->TileSprite->SetSize(tileSize, tileSize); // Explicit SetSize so that missing textures still get a size
                tileToLoad->SetTilePosition(i * scaledSize, j * scaledSize);

                TileDescriptionEntry* textureNameNeeded = this->GameWorld->TileMapping->Entries->Single([tileToLoad](TileDescriptionEntry* entry) { return tileToLoad->TileIdentifier == entry->id; });

                if (textureNameNeeded == NULL)
                    continue;

                tileToLoad->TileSprite->SetTextureName(textureNameNeeded->TextureName);
            }
        }

        mapIt++;
    }
}

void FantasyGame::InitGame()
{
    // Setup Player
    GamePlayer = new Player();
    Engine->AttachActor(GamePlayer);

    // Setup Camera
    FRectangle* fov = new FRectangle();
    Vector2<int>* scrollSpeed = new Vector2<int>();

    float cam_x = Settings->GetFloat("camera_starting_x", 0);
    float cam_y = Settings->GetFloat("camera_starting_y", 0);
    float cam_w = Settings->GetFloat("camera_fov_width") * scaledSize;
    float cam_h = Settings->GetFloat("camera_fov_height") * scaledSize;
    
    fov->Set(cam_x, cam_y, cam_w, cam_h);

    scrollSpeed->X = Settings->GetInt("camera_speed_x", 16);
    scrollSpeed->Y = Settings->GetInt("camera_speed_y", 16);

    MainCamera = new PlayerCamera(GamePlayer);
    MainCamera->SetupCamera(fov, scrollSpeed);

    Engine->AttachActor(MainCamera);

}

void FantasyGame::Start()
{
}

void FantasyGame::Play()
{
    while (true)
    {
        if (this->Engine->Graphics->IsTimeForFrame())
        {
            this->Update();

            Engine->Play();
        }
    }
}

void FantasyGame::Update()
{
    if (this->Engine->Keyboard->IsKeyClicked(Key::Q))
    {
        RandomGen rng = RandomGen();
        TgaFile* quickContent = new TgaFile();
        quickContent->Init(256, 256);

        int randomRed = rng.GetRandom(255);
        int randomGreen = rng.GetRandom(255);
        int randomBlue = rng.GetRandom(255);

        quickContent->FillColor(randomRed, randomGreen, randomBlue, 255);

        createdWindows->Add(QuickCreateWindow(quickContent));
    }

    if (this->Engine->Keyboard->IsKeyClicked(Key::E))
    {
        if (createdWindows->Count() > 0)
        {
            int lastIndex = createdWindows->Last();

            CloseQuickWindow(lastIndex);
        }
    }

    if (this->Engine->Keyboard->IsKeyClicked(Key::Num1))
    {
        auto it = TileIndexIdentifiers->GetContainer()->begin();
        while (it != TileIndexIdentifiers->GetContainer()->end())
        {
            BaseText* txt = *it;

            if (txt->IsVisible())
            {
                txt->Show(false);
            }
            else
            {
                txt->Show(true);
            }

            it++;
        }
    }

    if (this->Engine->Keyboard->IsKeyClicked(Key::Space))
    {
        if (DebugCheatsMenu->BackPlate->IsVisible())
        {
            DebugCheatsMenu->Hide();
        }
        else
        {
            DebugCheatsMenu->Show();
        }
    }

    Engine->Graphics->Viewport->X = MainCamera->CameraFieldOfView->Left;
    Engine->Graphics->Viewport->Y = MainCamera->CameraFieldOfView->Top;

}
