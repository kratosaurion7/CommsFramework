#pragma once

class BaseSprite;
class FPosition;

class Tile
{
public:
    Tile();
    ~Tile();

    // This is the original position of the tile
    FPosition* OriginalPosition;

    // This position is the current position depending on the game camera
    FPosition* Position;

    BaseSprite* TileSprite;
};

