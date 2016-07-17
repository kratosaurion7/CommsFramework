#include "World.h"

#include <PointerList.h>
#include <XmlReader.h>

#include "AreaGrid.h"

World::World()
{
    AreaGrid* defaultArea = new AreaGrid(NULL);
    
    Areas = new PointerList<AreaGrid*>();

    Areas->Add(defaultArea);
}


World::~World()
{
}

void World::SetupAreas(XmlNode* areasNode)
{

}
