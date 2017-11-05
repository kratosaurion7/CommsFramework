#pragma once

#include <Collections/ArrayList.h>
#include <Collections/PointerList.h>

class Tile;
class XmlNode;

class Map
{
    Map(int width, int height);
    ~Map();

    static Map* CreateFromXML(XmlNode* mapConfig);

    Tile*** Tiles;

    PointerList<Tile*>* TilesList;
};

