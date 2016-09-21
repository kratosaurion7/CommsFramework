#pragma once

class Map;
struct TileDescriptionList;

#include <PointerList.h>

class World
{
public:
    World();
    ~World();

    PointerList<Map*>* Maps;

    TileDescriptionList* TileMapping;

	static World* CreateWorldFromXml(std::string xmlPath);
};