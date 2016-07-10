#include "FantasyGame.h"

#include <cassert>

#include <GameEngine.h>
#include <Vectors.h>

#include "World.h"
#include "AreaGrid.h"
#include "LocalGrid.h"

#include "Player.h"
#include "PlayerCamera.h"



FantasyGame::FantasyGame()
{
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

void FantasyGame::Start(Game_Start_Params startingParams)
{
    
}

void FantasyGame::Update()
{
    
}