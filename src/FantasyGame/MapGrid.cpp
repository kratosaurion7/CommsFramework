#include "MapGrid.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <TextureRepository.h>
#include <FPosition.h>
#include <BaseSprite.h>

#include "Tile.h"


MapGrid::MapGrid()
{
}


MapGrid::~MapGrid()
{
}

void MapGrid::Setup(int height, int width)
{
    this->tiles = new Tile**[height];

    for (int i = 0; i < height; i++)
    {
        this->tiles[i] = new Tile*[width];

        for (int j = 0; j < width; j++)
        {
            Tile* newTile = new Tile();
            newTile->TileSprite = this->Engine->CreateSprite();
            newTile->TileSprite->Show(true);
            newTile->TileSprite->SetScale(4);
            newTile->TileSprite->SetPos(j * 64, i * 64);
            newTile->Position->X = j;
            newTile->Position->Y = i;

            //newTile->TileSprite->SetTexture(this->Engine->Graphics->TextureRepo->LoadTexture("Grass"));
            BaseTexture* tex = this->Engine->Graphics->TextureRepo->GetTextureByName("Grass01.png");
            newTile->TileSprite->SetTexture(tex);

            this->tiles[i][j] = newTile;
        }
    }
}

Tile* MapGrid::Get(int x, int y)
{
    return tiles[y][x];
}

void MapGrid::Set(int x, int y, Tile * tile)
{
    tiles[y][x] = tile;
}

void MapGrid::SetTileTexture(int x, int y, BaseTexture * texture)
{
    Tile* tile = this->Get(x, y);

    tile->TileSprite->SetTexture(texture);
}
