#pragma once

#include <string>

#include "FileReader.h"

#include "BaseList.h"
#include "PointerList.h"

#include "Resource.h"
#include "ResourceContainer.h"
#include "GameModule.h"
#include "GameModule.h"
#include "XmlReader.h"
#include "Models.h"

class Resource;
class GameModule;
class ResourceContainer;

struct ResourceManagerInitParams {

	std::string AssetRootFolder;

	std::string ConfigFileLocation;

};

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Init(ResourceManagerInitParams* initParams);

    void ParseConfigFiles();

    std::string PathToAssetsFolder;

    std::string configFileLocation;

	Resource* GetResource(std::string name, GameModule* targetModule = NULL);

	PointerList<Resource*> GetSpriteResources(std::string spriteName, GameModule* targetModule = NULL);

	PointerList<Resource*>* Resources;
    
	char* GetResourceDataFromStore(Resource* res, int& dataLenght, GameModule* targetModule = NULL);

private:
	ResourceManagerInitParams* startingParams;

    BaseList<std::string>* secondaryConfigFiles;

	PointerList<GameModule*>* Modules;
	PointerList<ResourceContainer*>* ResourceContainers;

	PointerList<Resource*>* CreateListOfResourcesFromXmlNodes(PointerList<XmlNode*> &resourceNodes);
	PointerList<ResourceContainer*>* CreateListOfContainersFromXmlNodes(PointerList<XmlNode*> &resourceNodes);

	PointerList<SpriteDescriptor*>* CreateSpritesFromXmlNodes(PointerList<XmlNode*> &spriteNodes);

};

