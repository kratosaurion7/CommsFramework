#pragma once

class Tile;
class BaseTexture;

#include <BaseActor.h>

class MapGrid : public BaseActor
{
public:
    MapGrid();
    ~MapGrid();

    void Setup(int height, int width);

    Tile* Get(int x, int y);
    void Set(int x, int y, Tile* tile);

    void SetTileTexture(int x, int y, BaseTexture* texture);

private:
    // 2D array of Tile*
    Tile*** tiles;
};

