#pragma once

class World;
class AreaGrid;
class LocalGrid;

#include <PointerList.h>

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();

    World* GameWorld;
};
