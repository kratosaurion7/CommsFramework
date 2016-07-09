#pragma once

class AreaGrid;

#include <PointerList.h>

class World
{
public:
    World();
    ~World();

    PointerList<AreaGrid*> Areas;

    std::string WorldName;
};

