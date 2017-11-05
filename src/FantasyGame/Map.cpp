#include "Map.h"

#include <XML/XmlReader.h>

#include "Tile.h"

Map::Map(int width, int height)
{
    this->Tiles = new Tile**[height];

    for (int i = 0; i < height; i++)
    {
        this->Tiles[i] = new Tile*[width];

        for (int j = 0; j < width; j++)
        {
            Tile* newTile = new Tile();

            this->Tiles[i][j] = newTile;
            this->TilesList->Add(newTile);
        }
    }

}

Map::~Map()
{

}

Map *Map::CreateFromXML(XmlNode *mapConfig)
{
    return nullptr;
}
