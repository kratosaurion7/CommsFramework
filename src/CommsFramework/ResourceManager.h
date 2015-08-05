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

class Resource;
class GameModule;
class ResourceContainer;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Init(std::string configFile);

    void ParseConfigFiles();

    std::string PathToAssetsFolder;

    std::string configFileLocation;

	Resource* GetResource(std::string name, GameModule* targetModule = NULL);

	PointerList<Resource*> GetSpriteResources(std::string spriteName, GameModule* targetModule = NULL);

	PointerList<Resource*>* Resources;
    
	char* GetResourceDataFromStore(Resource* res, int& dataLenght, GameModule* targetModule = NULL);

private:
    BaseList<std::string>* secondaryConfigFiles;

	PointerList<GameModule*>* Modules;
	PointerList<ResourceContainer*>* ResourceContainers;

	PointerList<Resource*>* CreateListOfResourcesFromXmlNodes(PointerList<XmlNode*> &resourceNodes);
	PointerList<ResourceContainer*>* CreateListOfContainersFromXmlNodes(PointerList<XmlNode*> &resourceNodes);

};

