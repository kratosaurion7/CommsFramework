#include "Tile.h"

#include <BaseSprite.h>
#include <BaseText.h>
#include <FPosition.h>

Tile::Tile()
{
    Position = new FPosition();
}


Tile::~Tile()
{
    delete(Position);
}

void Tile::SetTilePosition(FPosition* pos)
{
    this->Position = pos;
    this->TileSprite->SetPos(*pos);
    this->TileHelpText->SetPos(*pos);
}

void Tile::SetTilePosition(float x, float y)
{
    if (Position != NULL)
    {
        delete(Position);
    }

    Position = new FPosition(x, y);

    this->SetTilePosition(Position);
}
