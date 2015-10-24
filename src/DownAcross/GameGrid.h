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

    void RefreshGridTileInformations();

protected:
    virtual void Update();

private:

    PointerList<GridTile*>* Tiles;

    PointerList<InfoTile*>* InfoTiles;

    int GetZeroesOfRow(int rowNb);
    int GetSumOfRow(int rowNb);

    int GetZeroesOfColumn(int colNb);
    int GetSumOfColumn(int colNb);

    GridTileState cheatAppliedState = Covered;
};

