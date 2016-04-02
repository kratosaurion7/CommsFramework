#include "Tile.h"

#include <BaseSprite.h>
#include <FPosition.h>

Tile::Tile()
{
    Position = new FPosition();
}


Tile::~Tile()
{
    delete(Position);
}
