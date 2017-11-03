#pragma once

class Map;
struct TileDescriptionList;

#include <Collections/PointerList.h>

class World
{
public:
    World();
    ~World();

    PointerList<Map*>* Maps;

    TileDescriptionList* TileMapping;

	static World* CreateWorldFromXml(std::string xmlPath);
};