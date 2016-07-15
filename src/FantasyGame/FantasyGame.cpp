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

    GamePlayer = new Player();
    MainCamera = new PlayerCamera(GamePlayer);

    FloatVec* camPosition = new FloatVec(0, 0);
    MainCamera->SetCameraPosition(camPosition);

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

void FantasyGame::Start(Game_Start_Params* startingParams)
{
    auto it = startingParams->Spritesheets->GetContainer()->begin();
    while (it != startingParams->Spritesheets->GetContainer()->end())
    {
        Spritesheet* sheet = (*it);

        Engine->Graphics->AddSpritesheet(sheet);

        it++;
    }

    GameWorld = new World(NULL);

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

void FantasyGame::ReadXmlConfigFiles()
{
	XDirectory dir = XDirectory("assets");
	auto files = dir.GetFiles(true);

	for (XFile* file : *files->GetContainer())
	{
		if (file->FileName.find("_config.xml", 0) != std::string::npos)
		{
			XmlReader* reader = new XmlReader();
			reader->LoadFile(file->FilePath);

			reader->FindNodes("");
		}
	}

}

Game_Start_Params* FantasyGame::ReadParametersConfig(std::string configFilePath)
{
	Game_Start_Params* retParams = new Game_Start_Params();

	XmlReader file = XmlReader();
	file.LoadFile(configFilePath);

    // GET GAME NAME
	std::string gameName = file.FindNode("game")->FindNode("GameName")->Contents();
	retParams->GameName = gameName;

    // GET SPRITESHEETS
    retParams->Spritesheets = new PointerList<Spritesheet*>();
    PointerList<XmlNode*>* spritesheetNodes = file.FindNodes("Spritesheet");
    auto spritesheetIter = spritesheetNodes->GetContainer()->begin();
    while (spritesheetIter != spritesheetNodes->GetContainer()->end())
    {
        XmlNode* node = (*spritesheetIter);

        std::string spritesheetPath = node->Contents();

        Spritesheet* newSpritesheet = new Spritesheet(spritesheetPath, this->Engine->Graphics);

        retParams->Spritesheets->Add(newSpritesheet);

        spritesheetIter++;
    }

    // GET CAMERA OPTIONS
    auto cameraNode = file.GetNode("camera");
    auto cameraStartingPositionX = std::stof(cameraNode->GetNode("StartingPosition")->GetNode("X")->Contents());
    auto cameraStartingPositionY = std::stof(cameraNode->GetNode("StartingPosition")->GetNode("Y")->Contents());

    auto cameraHeight = std::stof(cameraNode->FindNode("Height")->Contents());
    auto cameraWidth = std::stof(cameraNode->FindNode("Width")->Contents());

    retParams->CameraStart = new FPosition(cameraStartingPositionX, cameraStartingPositionY);
    retParams->CameraSize = new FSize(cameraHeight, cameraWidth);

	return retParams;
}
