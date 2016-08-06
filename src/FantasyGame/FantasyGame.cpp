#include "FantasyGame.h"

#include <cassert>

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <Spritesheet.h>
#include <DrawObject.h>
#include <BaseSprite.h>
#include <Vectors.h>
#include <XmlReader.h>
#include <Spritesheet.h>
#include <FRectangle.h>
#include <FSize.h>
#include <XDirectory.h>
#include <XFile.h>
#include <SettingsRepository.h>
#include <TgaFile.h>
#include <Utils.h>

#include "ProgDef.h"
#include "World.h"
#include "AreaGrid.h"
#include "LocalGrid.h"

#include "Tile.h"

#include "Player.h"
#include "PlayerCamera.h"

FantasyGame::FantasyGame()
{
    Engine = new GameEngine();

    Engine->Init(SCALE_MULTIPLIER * GRID_WIDTH, SCALE_MULTIPLIER * GRID_HEIGHT);

    Settings = SettingsRepository::GetInstance();

    GamePlayer = new Player();
    MainCamera = new PlayerCamera(GamePlayer);

    Engine->AttachActor(GamePlayer);
    Engine->AttachActor(MainCamera);

    createdWindows = new BaseList<int>();
}

FantasyGame::~FantasyGame()
{
    Engine->DetachActor(MainCamera);
    Engine->DetachActor(GamePlayer);

    delete(MainCamera);
    delete(GamePlayer);
    delete(GameWorld);
}

void FantasyGame::Init()
{
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
	this->GameWorld = ReadWorldData("assets\\game_config.xml");

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

    CurrentArea = GameWorld->Areas->First();

    CurrentGrid = CurrentArea->Grids->First();

    CurrentGrid->Setup(20, 20);

    CurrentGrid->ShowGridTiles(true);

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

World* FantasyGame::ReadWorldData(std::string worldXmlConfigFile)
{
    XmlReader data = XmlReader();
	data.LoadFile(worldXmlConfigFile);
    auto worldsRoot = data.FindNode("Worlds");

    auto firstWorld = worldsRoot->GetNode("World");

    World* newWorld = new World();
    newWorld->WorldName = firstWorld->GetNode("WorldName")->Contents();

    return newWorld;
}
