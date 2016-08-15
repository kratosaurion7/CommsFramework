#include "MapLoader.h"

#include <XmlReader.h>

#include "LocalGrid.h"

MapLoader::MapLoader()
{
}


MapLoader::~MapLoader()
{
}

Map* MapLoader::LoadFromFile(std::string fileName)
{
    Map* result = new Map();

    XmlReader xml = XmlReader();
    xml.LoadFile(fileName);

    std::string mapName = xml.FindNode("map_name")->Contents();

    int mapWidth = atoi(xml.FindNode("tiles")->GetAttribute("width").AttributeValue);
    std::string tileDataString = xml.FindNode("tiles")->Contents();

    return result;
}
