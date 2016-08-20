#pragma once

class Tile;
class BaseTexture;

#include <BaseActor.h>
#include <PointerList.h>

class Map : public BaseActor
{
public:
    Map();
    ~Map();

    void Setup(int height, int width);

    Tile* Get(int x, int y);
    void Set(int x, int y, Tile* tile);

    void SetTileTexture(int x, int y, BaseTexture* texture);

    void ShowGridTiles(bool show);

    // 2D array of Tile*
    Tile*** tiles;
    
    // Same array of tiles but in an handy list
    PointerList<Tile*>* tilesList;

private:

};