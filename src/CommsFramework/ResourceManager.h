#pragma once

#include <string>

#include "FileReader.h"

#include "BaseList.h"
#include "PointerList.h"

#include "Resource.h"
#include "ResourceContainer.h"
#include "ResourceModule.h"
#include "ResourceModule.h"
#include "XmlReader.h"

class Resource;
class ResourceModule;

class ResourceManager
{
public:
	ResourceManager(std::string configFile);
	~ResourceManager();

    void ParseConfigFiles();

    std::string PathToAssetsFolder;

    std::string configFileLocation;

    char* GetResourceDataFromStore(Resource* res, int& dataLenght, std::string targetModule = "");

    PointerList<Resource*>* Resources;
    PointerList<ResourceContainer*>* ResourceContainers;
    PointerList<ResourceModule*>* Modules;

private:
    BaseList<std::string>* secondaryConfigFiles;

	PointerList<Resource*>* CreateListOfResourcesFromXmlNodes(PointerList<XmlNode*> &resourceNodes);
	PointerList<ResourceContainer*>* CreateListOfContainersFromXmlNodes(PointerList<XmlNode*> &resourceNodes);

};

