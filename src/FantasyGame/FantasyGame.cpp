#include "FantasyGame.h"

#include "World.h"
#include "AreaGrid.h"
#include "LocalGrid.h"

FantasyGame::FantasyGame()
{
    GameWorld = new World();
}


FantasyGame::~FantasyGame()
{
    delete(GameWorld);
}
