#include "AreaGrid.h"

#include "LocalGrid.h"
#include "Tile.h"

AreaGrid::AreaGrid(AreaCreateParams* params)
{
    LocalGrid* defaultGrid = new LocalGrid();
    
    Grids = new PointerList<LocalGrid*>();

    Grids->Add(defaultGrid);
}


AreaGrid::~AreaGrid()
{
}
