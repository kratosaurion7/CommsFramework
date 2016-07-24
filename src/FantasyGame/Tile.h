#pragma once

class BaseSprite;
class BaseText;
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
    BaseText* TileHelpText;

    void SetTilePosition(FPosition* pos);
    void SetTilePosition(float x, float y);
};

