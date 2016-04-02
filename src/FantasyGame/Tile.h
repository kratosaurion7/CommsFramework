#pragma once

class BaseSprite;
class FPosition;

class Tile
{
public:
    Tile();
    ~Tile();

    FPosition* Position;

    BaseSprite* TileSprite;
};

