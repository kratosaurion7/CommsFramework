#include "AreaGrid.h"

#include "LocalGrid.h"
#include "Tile.h"

AreaGrid::AreaGrid(AreaCreateParams* params)
{
    LocalGrid* defaultGrid = new LocalGrid(NULL);
    
    Grids->Add(defaultGrid);
}


AreaGrid::~AreaGrid()
{
}
