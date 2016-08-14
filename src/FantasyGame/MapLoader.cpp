#include "MapLoader.h"

#include <XmlReader.h>

#include "LocalGrid.h"

MapLoader::MapLoader()
{
}


MapLoader::~MapLoader()
{
}

LocalGrid* MapLoader::LoadFromFile(std::string fileName)
{
    LocalGrid* result = new LocalGrid();

    XmlReader xml = XmlReader();
    xml.LoadFile(fileName);

    return result;
}
