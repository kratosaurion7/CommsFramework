#include "FantasyGame.h"

#include <cassert>

#include "World.h"
#include "AreaGrid.h"
#include "LocalGrid.h"

#include "Player.h"
#include "PlayerCamera.h"

#include <GameEngine.h>

FantasyGame::FantasyGame()
{
    GameWorld = new World();

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

void FantasyGame::Update()
{
    
}