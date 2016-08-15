#pragma once

class Map;

#include <string>

class MapLoader
{
public:
    MapLoader();
    ~MapLoader();

    Map* LoadFromFile(std::string fileName);
};

