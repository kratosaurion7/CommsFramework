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

}

Map::~Map()
{
}

Map * Map::CreateFromXml(std::string xmlPath)
{
	return nullptr;
}
