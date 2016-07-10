#pragma once

class Tile;
class LocalGrid;

#include <PointerList.h>

struct AreaCreateParams
{

};

class AreaGrid
{
public:
    AreaGrid(AreaCreateParams* params);
    ~AreaGrid();

    PointerList<LocalGrid*>* Grids;
};

