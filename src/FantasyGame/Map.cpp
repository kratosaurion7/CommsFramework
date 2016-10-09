#include "Map.h"

#include <XmlReader.h>

#include "ProgDef.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <BaseText.h>
#include <BaseTexture.h>
#include <TextureRepository.h>
#include <FPosition.h>
#include <BaseSprite.h>
#include <RandomGen.h>
#include <PathLoader.h>

#include "FantasyGame.h"
#include "Tile.h"

Map::Map(int width, int height)
{
	this->Width = width;
	this->Height = width;

	this->Tiles = new Tile**[height];

    this->TilesList = new PointerList<Tile*>();
    

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

Map* Map::CreateFromXml(std::string xmlPath)
{
	XmlReader mapReader;
	mapReader.LoadFile(PathLoader::GetPath(xmlPath));

	// Get the size properties to create a Map instance
	int mapWidth;
	int mapHeight;

	auto sizeElement = mapReader.FindNode("map_size");
	mapWidth = atoi(sizeElement->GetAttribute("width").AttributeValue);
	mapHeight = atoi(sizeElement->GetAttribute("height").AttributeValue);

	Map* ret = new Map(mapWidth, mapHeight);

	// Then read the xml to generate the layout of the map tiles

	auto mapDataElement = mapReader.FindNode("map_data");

	// No map data, create a random layout
	if (mapDataElement == NULL)
	{
        ret->InitializeDefaultMap();
	}
	else
	{
		// Woah, you're asking a lot here.
	}

	return ret;
}

void Map::InitializeDefaultMap()
{
    for (int i = 0; i < this->Height; i++)
    {
        for (int j = 0; j < this->Width; j++)
        {
            Tile* targetTile = this->Tiles[i][j];

            targetTile->Coordinate = new FPosition(j, i);

            targetTile->TileIdentifier = (i + j) % 10;
        }
    }
}
