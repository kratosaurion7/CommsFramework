#pragma once

class AreaGrid;

#include <string>
#include <PointerList.h>

struct WorldCreateParams
{

};

class World
{
public:
    World(WorldCreateParams* params);
    ~World();

    PointerList<AreaGrid*>* Areas;

    std::string WorldName;
};

