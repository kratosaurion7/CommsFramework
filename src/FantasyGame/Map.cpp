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

Map::Map()
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

Map::~Map()
{
}

Map * Map::CreateFromXml(std::string xmlPath)
{
	XmlReader mapReader = XmlReader();
	Map* ret = new Map();

	mapReader.LoadFile(xmlPath);

	std::string mapName = mapReader.GetNode("map_name")->Contents();
	std::string mapData;
	int mapWidth;
	XmlNode* tilesNode = mapReader.GetNode("tiles");
	mapData = tilesNode->Contents();
	mapWidth = atoi(tilesNode->GetAttribute("width").AttributeValue);

	ret->MapName = mapName;
	ret->RawMapData = new char[mapData.length()];
	memcpy(ret->RawMapData, mapData.data(), mapData.length());

	return ret;
}

void Map::ProcessMapData()
{
}

void Map::Setup(int height, int width)
{
    FantasyGame* game = GetGameInstance();

    RandomGen rnd = RandomGen();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Tile* setupTile = this->tiles[i][j];

            int randomNumberIndex = rnd.GetRandom(this->Engine->Graphics->TextureRepo->loadedTextures->Count());
            BaseTexture* tex = this->Engine->Graphics->TextureRepo->loadedTextures->Get(randomNumberIndex);
            BaseText* text = this->Engine->CreateText(std::to_string(j + (i * height)));
            text->SetFont(this->Engine->GetGameDefaultFont());
            text->SetPos(setupTile->TileSprite->GetPos());
            text->Show(true);
            
            game->TileIndexIdentifiers->Add(text);
            
            setupTile->TileHelpText = text;
            /*BaseTexture* textureFromText = text->GetTextImage();
            tex->OverlayTexture(textureFromText);*/

            setupTile->TileSprite->SetTexture(tex);

            setupTile->OriginalPosition = new FPosition(setupTile->TileSprite->GetPos());
            setupTile->Position = new FPosition(setupTile->TileSprite->GetPos());
        }
    }
}

Tile* Map::Get(int x, int y)
{
    return tiles[y][x];
}

void Map::Set(int x, int y, Tile * tile)
{
    tiles[y][x] = tile;
}

void Map::SetTileTexture(int x, int y, BaseTexture* texture)
{
    Tile* tile = this->Get(x, y);

    tile->TileSprite->SetTexture(texture);
}

void Map::ShowGridTiles(bool show)
{
    auto it = tilesList->GetContainer()->begin();
    while (it != tilesList->GetContainer()->end())
    {
        Tile* iter = (*it);

        iter->TileSprite->Show(show);

        it++;
    }
}
