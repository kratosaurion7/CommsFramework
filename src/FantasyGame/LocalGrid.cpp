#include "LocalGrid.h"

#include "ProgDef.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <TextureRepository.h>
#include <FPosition.h>
#include <BaseSprite.h>
#include <RandomGen.h>

#include "Tile.h"

LocalGrid::LocalGrid(LocalGridCreateParam* params)
{
    int height = 20;
    int width = 20;

    tilesList = new PointerList<Tile*>();

    this->tiles = new Tile**[height];

    for (int i = 0; i < height; i++)
    {
        this->tiles[i] = new Tile*[width];

        for (int j = 0; j < width; j++)
        {
            Tile* newTile = new Tile();
            newTile->TileSprite = this->Engine->CreateSprite();
            newTile->TileSprite->Show(true);
            newTile->TileSprite->SetScale(SCALE_FACTOR);
            newTile->TileSprite->SetPos((float)j * SCALE_MULTIPLIER, (float)i * SCALE_MULTIPLIER);
            newTile->Position->X = (float)j;
            newTile->Position->Y = (float)i;

            this->tiles[i][j] = newTile;
            tilesList->Add(newTile);
        }
    }
}

LocalGrid::~LocalGrid()
{
}

void LocalGrid::Setup(int height, int width)
{
    RandomGen rnd = RandomGen();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Tile* setupTile = this->tiles[i][j];

            int randomNumberIndex = rnd.GetRandom(this->Engine->Graphics->TextureRepo->loadedTextures->Count());
            BaseTexture* tex = this->Engine->Graphics->TextureRepo->loadedTextures->Get(randomNumberIndex);
            setupTile->TileSprite->SetTexture(tex);

            setupTile->OriginalPosition = new FPosition(setupTile->TileSprite->GetPos());
            setupTile->Position = new FPosition(setupTile->TileSprite->GetPos());
        }
    }
}

Tile* LocalGrid::Get(int x, int y)
{
    return tiles[y][x];
}

void LocalGrid::Set(int x, int y, Tile * tile)
{
    tiles[y][x] = tile;
}

void LocalGrid::SetTileTexture(int x, int y, BaseTexture * texture)
{
    Tile* tile = this->Get(x, y);

    tile->TileSprite->SetTexture(texture);
}

void LocalGrid::ShowGridTiles(bool show)
{
    auto it = tilesList->GetContainer()->begin();
    while (it != tilesList->GetContainer()->end())
    {
        Tile* iter = (*it);

        iter->TileSprite->Show(show);

        it++;
    }
}
