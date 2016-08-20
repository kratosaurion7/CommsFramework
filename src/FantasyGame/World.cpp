#include "World.h"

#include "Map.h"

World::World()
{
    Maps = new PointerList<Map*>();
}

World::~World()
{
    Maps->Release();

    delete(Maps);
}
