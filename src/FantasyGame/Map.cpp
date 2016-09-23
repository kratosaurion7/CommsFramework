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

#include "FantasyGame.h"
#include "Tile.h"

Map::Map(int width, int height)
{
	this->Width = width;
	this->Height = width;

	this->Tiles = new Tile**[height];

	for (int i = 0; i < height; i++)
	{
		this->Tiles[i] = new Tile*[width];

		for (int j = 0; j < width; j++)
		{
			Tile* newTile = new Tile();

			this->Tiles[i][j] = newTile;
		}
	}
}

Map::~Map()
{
}

Map* Map::CreateFromXml(std::string xmlPath)
{
	XmlReader mapReader;
	mapReader.LoadFile(xmlPath);

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

	}
	else
	{
		// Woah, you're asking a lot here.
	}

	return ret;
}
