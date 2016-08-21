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

    // Init the engine first, this gives access to the services proposed by the engine
    InitEngine();

    // Next we can init the game world, we can't fully create the tiles yet
    // because the graphics are not loaded yet.
    World* root = ReadWorldXml("assets\\World.xml");
    this->GameWorld = root;

    // Now that we have a World to load, we can check and load the assets that are needed
    InitGraphics();

    // Finally, we init the game. Player, camera, etc. After that, the game is ready to play.
    InitGame();

    // Extract sprites
    auto pred = [](std::string p) {
        return p.find("spritesheet_") == 0;
    };

    auto spritesheetValues = Settings->GetWhere(pred);

    for (char* sPath : *spritesheetValues->GetContainer())
    {
        Spritesheet* ssheet = new Spritesheet(sPath, this->Engine->Graphics);

        Engine->Graphics->AddSpritesheet(ssheet);
    }

    // Setup Game World
	//this->GameWorld = ReadWorldData("assets\\game_config.xml");

    // Setup Camera
    _tile_size = std::stof(Settings->Get("graphic_tile_size"));

    _cameraX = std::stof(Settings->Get("camera_starting_x"));
    _cameraY = std::stof(Settings->Get("camera_starting_y"));

    _cameraHeights = std::stof(Settings->Get("camera_fov_height"));
    _cameraWidth = std::stof(Settings->Get("camera_fov_width"));

    FRectangle* camFov = new FRectangle(_cameraX, _cameraY, _cameraHeights * SCALE_MULTIPLIER, _cameraWidth * SCALE_MULTIPLIER);

    Vector2<int>* camSpeed = new Vector2<int>();
    camSpeed->X = std::stoi(Settings->Get("camera_speed_x"));
    camSpeed->Y = std::stoi(Settings->Get("camera_speed_y"));

    MainCamera->SetupCamera(camFov, camSpeed);

    CurrentGrid = NULL; // TODO

    CurrentGrid->Setup(20, 20);

    CurrentGrid->ShowGridTiles(true);

    GamePlayer = new Player();
    Engine->AttachActor(GamePlayer);

    // Deletes
    delete(spritesheetValues);
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



    // Update the position of the tiles of the current grid
    // by offsetting their position by the camera's pos.
    auto it = this->CurrentGrid->tilesList->GetContainer()->begin();
    while (it != this->CurrentGrid->tilesList->GetContainer()->end())
    {
        Tile* iter = (*it);

        auto tilePos = iter->OriginalPosition;

        float x = tilePos->X - MainCamera->CameraFieldOfView->Left;
        float y = tilePos->Y - MainCamera->CameraFieldOfView->Top;

        iter->SetTilePosition(x, y);

        //if (MainCamera->CameraFieldOfView->Intersect(&iter->TileSprite->GetRectangle()))
        //{
        //    iter->TileSprite->Show(true);
        //}
        //else
        //{
        //    iter->TileSprite->Show(false);
        //}
        
        it++;
    }
}

void FantasyGame::ReadCoreSettings()
{
    // TODO : Find a way to copy the config file from somewhere else than the assets
    Settings->ReadFromXml("assets\\config.xml");

    this->assetsPath = Settings->Get("assets_root");

    
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

World* FantasyGame::ReadWorldXml(std::string rootWorldFileName)
{
    XmlReader worldFileReader = XmlReader();
    World* ret = new World();

    worldFileReader.LoadFile(rootWorldFileName);

    // Read the <tiles> node
    auto mapNodes = worldFileReader.GetNode("maps")->GetNodes("map");

    auto it = ITBEGIN(mapNodes);
    while (it != ITEND(mapNodes))
    {
        XmlNode* element = *it;

        std::string mapName = element->GetAttribute("name").AttributeValue;
        std::string mapFilepath = element->GetAttribute("source").AttributeValue;

        Map* newMap = ReadMapData(mapFilepath);

        ret->Maps->Add(newMap);

        it++;
    }

    // Read the <tile_description> node
    auto descriptionNode = worldFileReader.FindNode("tile_description")->GetNodes("tile");
    TileDescriptionList* descList = new TileDescriptionList();
    ret->TileMapping = descList;

    descList->Entries = new PointerList<TileDescriptionEntry*>();

    auto descIt = ITBEGIN(descriptionNode);
    while (descIt != ITEND(descriptionNode))
    {
        XmlNode* element = *descIt;

        TileDescriptionEntry* newEntry = new TileDescriptionEntry();
        newEntry->id = atoi(element->GetAttribute("id").AttributeValue);
        newEntry->TextureName = element->GetAttribute("texture").AttributeValue;

        descList->Entries->Add(newEntry);

        descIt++;
    }

    return ret;
}

Map* FantasyGame::ReadMapData(std::string mapFileName)
{
    XmlReader mapReader = XmlReader();
    Map* ret = new Map();

    mapReader.LoadFile(this->assetsPath + mapFileName);

    std::string mapName = mapReader.GetNode("map_name")->Contents();
    std::string mapData;
    int mapWidth;
    XmlNode* tilesNode = mapReader.GetNode("tiles");
    mapData = tilesNode->Contents();
    mapWidth = atoi(tilesNode->GetAttribute("width").AttributeValue);

    ret->MapName = mapName;
    ret->RawMapData = new char[mapData.length()];
    memcpy(ret->RawMapData, mapData.data(), mapData.length());

    return ret;

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
    }


    //BaseList<std::string>* loadQueue = new BaseList<std::string>();

    //auto it = ITBEGIN(this->GameWorld->Maps);
    //while (it != ITEND(this->GameWorld->Maps))
    //{
    //    Map* iter = *it;

    //    auto mappingIter = ITBEGIN(iter->TileMappings->Entries);
    //    while (mappingIter != ITEND(iter->TileMappings->Entries))
    //    {
    //        TileDescriptionEntry* entry = *mappingIter;

    //        if (!loadQueue->ContainsItem(entry->TextureName))
    //        {
    //            loadQueue->Add(entry->TextureName);
    //        }
    //    }

    //    it++;
    //}
}

void FantasyGame::InitGame()
{

}

void FantasyGame::ReadConfig()
{
    SettingsRepository* settings = SettingsRepository::GetInstance();

	XDirectory dir = XDirectory("assets");
	auto files = dir.GetFiles(true);

	// Take all XML files and read the <parameters> to extract the config from them
	for (XFile* file : *files->GetContainer())
	{
		if (file->FileName.find("_config.xml", 0) != std::string::npos)
		{
			XmlReader reader = XmlReader();
			reader.LoadFile(file->FilePath);

            auto paramNodes = reader.FindNodes("parameters");

            for (XmlNode* pNodeContainer : *paramNodes->GetContainer())
            {
                auto container = pNodeContainer->GetChildNodes(true);

                for (XmlNode* pNode : *container->GetContainer())
                {
                    std::string parameterName = pNode->NodeName();
                    std::string value = pNode->Contents();

                    char* valueData = new char[value.length()];
                    strcpy(valueData, value.c_str());

                    settings->Register(parameterName, valueData);
                }
            }
		}
	}

	delete(files);
}