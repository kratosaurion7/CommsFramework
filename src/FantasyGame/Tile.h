#pragma once

class BaseSprite;
class BaseText;
class FPosition;

class Tile
{
public:
    Tile();
    ~Tile();

    // ----- Logical Properties -----

    // What texture to show on the tile. This is set at first when the Graphic
    // engine is not ready to create sprites yet.
    int TileIdentifier;

    // This is the map coordinate of the tile
    FPosition* Coordinate;


    // ----- Graphical Properties -----
    // This is the original position of the tile
    FPosition* OriginalPosition;

    // This position is the current position depending on the game camera
    FPosition* Position;

    BaseSprite* TileSprite;
    BaseText* TileHelpText;

    void SetTilePosition(FPosition* pos);
    void SetTilePosition(float x, float y);
};

