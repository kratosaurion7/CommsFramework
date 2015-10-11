#pragma once

#include <BaseActor.h>

class GameGrid : public BaseActor
{
public:
    GameGrid(int squareSize);
    ~GameGrid();

    void Setup();

    int SquareSize;

    int BlockSize = 64;

    int SpaceSize = 20;
};

