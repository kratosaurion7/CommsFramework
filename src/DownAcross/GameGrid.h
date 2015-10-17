#pragma once

#include <PointerList.h>
#include <BaseActor.h>

#include "GridTile.h"
#include "InfoTile.h"

class GameGrid : public BaseActor
{
public:
    GameGrid(int squareSize, GameEngine* engine);
    ~GameGrid();

    void Setup();

    int SquareSize;

    int BlockSize = 64;

    int SpaceSize = 20;
private:

    PointerList<GridTile*>* Tiles;

    PointerList<InfoTile*>* InfoTiles;
};

