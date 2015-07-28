#pragma once

#include <string>

#include "FileReader.h"

#include "BaseList.h"
#include "PointerList.h"

#include "Resource.h"
#include "ResourceContainer.h"
#include "XmlReader.h"

class Resource;

class ResourceManager
{
public:
	ResourceManager(std::string configFile);
	~ResourceManager();

    void ParseConfigFiles();

    std::string PathToAssetsFolder;

    std::string configFileLocation;

    BaseList<std::string>* secondaryConfigFiles;

    PointerList<Resource*>* resources;
    PointerList<ResourceContainer*>* resourceContainers;

private:

	PointerList<Resource*>* CreateListOfResourcesFromXmlNodes(PointerList<XmlNode*> &resourceNodes);
	PointerList<ResourceContainer*>* CreateListOfContainersFromXmlNodes(PointerList<XmlNode*> &resourceNodes);

};

