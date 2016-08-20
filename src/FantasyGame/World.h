#pragma once

class Map;

#include <PointerList.h>

class World
{
public:
    World();
    ~World();

    PointerList<Map*>* Maps;
};