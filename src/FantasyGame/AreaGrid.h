#pragma once

class Tile;
class LocalGrid;

#include <PointerList.h>

class AreaGrid
{
public:
    AreaGrid();
    ~AreaGrid();

    PointerList<LocalGrid*> Grids;
};

