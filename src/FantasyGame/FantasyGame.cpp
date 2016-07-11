#include "FantasyGame.h"

#include <cassert>

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <Spritesheet.h>
#include <DrawObject.h>
#include <BaseSprite.h>
#include <Vectors.h>
#include <XmlReader.h>

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

    Spritesheet* sp = new Spritesheet("assets//spritesheet.xml", Engine->Graphics);
    Engine->Graphics->AddSpritesheet(sp);

    GameWorld = new World(NULL);

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

Game_Start_Params * FantasyGame::ReadParametersConfig(std::string configFilePath)
{
	Game_Start_Params* retParams = new Game_Start_Params();

	XmlReader file = XmlReader();
	file.LoadFile(configFilePath);

	

	return retParams;
}
