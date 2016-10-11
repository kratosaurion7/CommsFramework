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
#include <SettingsRepository.h>
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

    this->Settings = SettingsRepository::GetInstance();
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

    PathLoader::SetBasePath("assets\\");

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

void FantasyGame::ReadCoreSettings()
{
    // TODO : Find a way to copy the config file from somewhere else than the assets
    Settings->ReadFromXml("config.xml");

    this->assetsPath = Settings->Get("assets_root");

    PathLoader::SetBasePath(this->assetsPath);
}

void FantasyGame::InitEngine()
{
    Engine = new GameEngine();

    Engine->Init(SCALE_MULTIPLIER * GRID_WIDTH, SCALE_MULTIPLIER * GRID_HEIGHT);

    Settings = SettingsRepository::GetInstance();

    MainCamera = new PlayerCamera(GamePlayer);

    Engine->AttachActor(MainCamera);

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
                tileToLoad->TileSprite->SetScale(4);
                tileToLoad->TileSprite->SetSize(16, 16);
                tileToLoad->SetTilePosition(i * 64, j * 64);

                TileDescriptionEntry* textureNameNeeded = this->GameWorld->TileMapping->Entries->Single([tileToLoad](TileDescriptionEntry* entry) { return tileToLoad->TileIdentifier == entry->id; });

                if (textureNameNeeded == NULL)
                    continue;

                BaseTexture* textureForTile = this->Engine->Graphics->TextureRepo->GetTexture(textureNameNeeded->TextureName);

                if (textureForTile == NULL)
                    continue;

                tileToLoad->TileSprite->SetTexture(textureForTile);
            }
        }

        mapIt++;
    }
}

void FantasyGame::InitGame()
{

}