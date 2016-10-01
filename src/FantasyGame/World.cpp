#include "World.h"

#include <XmlReader.h>
#include <PathLoader.h>

#include "MapXmlStructs.h"

#include "Map.h"

World::World()
{
    Maps = new PointerList<Map*>();
}

World::~World()
{
    Maps->Release();

    delete(Maps);
}

World* World::CreateWorldFromXml(std::string xmlPath)
{
	XmlReader worldFileReader = XmlReader();
	World* ret = new World();

	worldFileReader.LoadFile(PathLoader::GetPath(xmlPath));

	// Read the <tiles> node
	auto mapNodes = worldFileReader.GetNode("maps")->GetNodes("map");

	auto it = ITBEGIN(mapNodes);
	while (it != ITEND(mapNodes))
	{
		XmlNode* element = *it;

		std::string mapName = element->GetAttribute("name").AttributeValue;
		std::string mapFilepath = element->GetAttribute("source").AttributeValue;

		Map* newMap = Map::CreateFromXml(mapFilepath);

		ret->Maps->Add(newMap);

		it++;
	}

	// Read the <tile_description> node
	auto descriptionNode = worldFileReader.FindNode("tile_description")->GetNodes("tile");
	TileDescriptionList* descList = new TileDescriptionList();
	ret->TileMapping = descList;

	descList->Entries = new PointerList<TileDescriptionEntry*>();

	auto descIt = ITBEGIN(descriptionNode);
	while (descIt != ITEND(descriptionNode))
	{
		XmlNode* element = *descIt;

		TileDescriptionEntry* newEntry = new TileDescriptionEntry();
		newEntry->id = atoi(element->GetAttribute("id").AttributeValue);
		newEntry->TextureName = element->GetAttribute("texture").AttributeValue;

		descList->Entries->Add(newEntry);

		descIt++;
	}

	return ret;
}
