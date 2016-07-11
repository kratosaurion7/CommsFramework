#include "World.h"

#include "AreaGrid.h"

World::World(WorldCreateParams* params)
{
    AreaGrid* defaultArea = new AreaGrid(NULL);
    
    Areas = new PointerList<AreaGrid*>();

    Areas->Add(defaultArea);
}


World::~World()
{
}
