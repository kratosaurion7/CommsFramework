#pragma once

class LocalGrid;

#include <string>

class MapLoader
{
public:
    MapLoader();
    ~MapLoader();

    LocalGrid* LoadFromFile(std::string fileName);
};

