#pragma once

class GameEngine;
class BaseSprite;

#include <BaseActor.h>

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

