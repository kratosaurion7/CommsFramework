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
    float _cameraX = std::stof(Settings->Get("camera_starting_x"));
    float _cameraY = std::stof(Settings->Get("camera_starting_y"));
    
    float _cameraHeights = std::stof(Settings->Get("camera_fov_height"));
    float _cameraWidth = std::stof(Settings->Get("camera_fov_width"));

    FloatVec* camPos = new FloatVec(_cameraX, _cameraY);
    MainCamera->SetCameraPosition(camPos);

    FSize* siz = new FSize(_cameraHeights, _cameraWidth);

    auto pred = [](std::string p) {
        return p.find("spritesheet_") == 0;
    };

    auto spritesheetValues = Settings->GetWhere(pred);

    for (char* sPath : *spritesheetValues->GetContainer())
    {
        Spritesheet* ssheet = new Spritesheet(sPath, this->Engine->Graphics);

        Engine->Graphics->AddSpritesheet(ssheet);
    }

    this->GameWorld = ReadWorldData("game_config.xml");
}

void FantasyGame::Start()
{
    GameWorld = this->ReadWorldData(NULL);

    CurrentArea = GameWorld->Areas->First();

    CurrentGrid = CurrentArea->Grids->First();

    CurrentGrid->Setup(20, 20);

    CurrentGrid->ShowGridTiles(true);
}

void FantasyGame::Play()
{
    while (true)
    {
        this->Update();

        Engine->Play();
    }
}

void FantasyGame::Update()
{
    // Update the position of the tiles of the current grid
    // by offsetting their position by the camera's pos.
    auto it = this->CurrentGrid->tilesList->GetContainer()->begin();
    while (it != this->CurrentGrid->tilesList->GetContainer()->end())
    {
        Tile* iter = (*it);

        auto tilePos = iter->OriginalPosition;

        float x = tilePos->X + MainCamera->CameraFieldOfView->Left;
        float y = tilePos->Y + MainCamera->CameraFieldOfView->Top;

        iter->TileSprite->SetPos(x, y);

        it++;
    }
}

void FantasyGame::ReadConfig()
{
    SettingsRepository* settings = SettingsRepository::GetInstance();

	XDirectory dir = XDirectory("assets");
	auto files = dir.GetFiles(true);

	for (XFile* file : *files->GetContainer())
	{
		if (file->FileName.find("_config.xml", 0) != std::string::npos)
		{
			XmlReader* reader = new XmlReader();
			reader->LoadFile(file->FilePath);

            auto paramNodes = reader->FindNodes("parameters");

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

}

World* FantasyGame::ReadWorldData(std::string worldXmlConfigFile)
{
    XmlReader data = XmlReader();
    auto worldsRoot = data.FindNode("Worlds");

    auto firstWorld = worldsRoot->GetNode("World");

    World* newWorld = new World();
    newWorld->WorldName = firstWorld->GetNode("WorldName")->Contents();

    return newWorld;
}
