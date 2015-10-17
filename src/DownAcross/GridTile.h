#pragma once

#include <BaseActor.h>

#include <BaseSprite.h>

enum GridTileState
{
    Covered,
    Revealed
};

class GridTile : public BaseActor
{
public:
    GridTile(int number, GameEngine* engine);
    ~GridTile();

    BaseSprite* TileSprite;

    BaseSprite *CoveredSprite;

    int tileNumber;

    void SetNewNumber(int newNumber);

    GridTileState tileState;

    void Update();

};

