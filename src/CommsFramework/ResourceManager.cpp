#include "ResourceManager.h"

#include "Resource.h"
#include "PointerList.h"

#include <queue>

#include "XmlReader.h"

ResourceManager::ResourceManager()
{
    secondaryConfigFiles = new BaseList<std::string>();
	Resources = new PointerList<Resource*>();
	ResourceContainers = new PointerList<ResourceContainer*>();
    Modules = new PointerList<GameModule*>();

    PathToAssetsFolder = "assets\\";
}

ResourceManager::~ResourceManager()
{
    delete(secondaryConfigFiles);
    
    Resources->Release();
    delete(Resources);

    ResourceContainers->Release();
    delete(ResourceContainers);

    Modules->Release();
    delete(Modules);
}

void ResourceManager::Init(std::string configFile)
{
	configFileLocation = configFile;

}

void ResourceManager::ParseConfigFiles()
{
	if (configFileLocation == "")
		return;

    std::string nextConfigFile = configFileLocation;

    std::queue<std::string> configQueue;

	configQueue.push(nextConfigFile);

	while (strcmp(nextConfigFile.c_str(), "") != 0)
    {
        XmlReader rdr = XmlReader();

        rdr.LoadFile(nextConfigFile.c_str());

		PointerList<XmlNode*>* resNodes = rdr.GetNodes("resource");
		auto newResources = CreateListOfResourcesFromXmlNodes(*resNodes);
		
		Resources->AddRange(newResources);

        auto rootNode = rdr.GetNode("config");
        auto moduleNameAttr = rootNode->GetAttribute("ModuleName");

        if (moduleNameAttr != NULL)
        {
            GameModule* module = NULL;
            
            for (int i = 0; i < Modules->Count(); i++)
            {
                GameModule* testModule = Modules->Get(i);

                if (testModule->ModuleName == moduleNameAttr->AttributeName)
                {
                    module = testModule;
                }
            }

            if(module == NULL)
                module = new GameModule();

            module->ModuleName = moduleNameAttr->AttributeValue;
            
            module->Resources->AddRange(newResources);

            Modules->Add(module);
        }

        delete(rootNode); // TEST ?

		// Delete the intermediate container, the resources created by CreateListOfResourcesFromXmlNodes are still alive but the temporary
		// container newResources is deleted.
		delete(newResources);

		PointerList<XmlNode*>* subConfigs = rdr.GetNodes("configFile");
		
		auto it = subConfigs->GetContainer()->begin();
		while (it != subConfigs->GetContainer()->end())
		{
			XmlNode* element = *it;

            std::string combinedPath = PathToAssetsFolder + element->GetAttribute("path")->AttributeValue;
			std::string configFileName = element->GetAttribute("path")->AttributeValue;

			configQueue.push(combinedPath);
			secondaryConfigFiles->Add(configFileName); // Add the config file name NOT prepended by the assets root folder path.

			it++;
		}
        
		PointerList<XmlNode*>* containers = rdr.GetNodes("container");
		auto newContainers = CreateListOfContainersFromXmlNodes(*containers);

		ResourceContainers->AddRange(newContainers);

		delete(newContainers);


		configQueue.pop();

		if (configQueue.empty())
		{
			nextConfigFile = "";
		}
		else 
		{
			nextConfigFile = configQueue.front();
		}

        subConfigs->Release();
        delete(subConfigs);
        resNodes->Release();
        delete(resNodes);
        containers->Release();
        delete(containers);
    }
}

char* ResourceManager::GetResourceDataFromStore(Resource* res, int& dataLenght, GameModule* targetModule)
{
	GameModule* moduleOfResource = NULL;

	for (int i = 0; i < Modules->Count();i++)
	{
		GameModule* nextModule = Modules->Get(i);

		if (strcmp(nextModule->ModuleName.c_str(), targetModule->ModuleName.c_str()) == 0)
		{
			moduleOfResource = nextModule;
			break;
		}
	}

	auto it = ResourceContainers->GetContainer()->begin();
	while (it != ResourceContainers->GetContainer()->end())
	{
		ResourceContainer* container = *it;
		
		if (container->Contains(res))
		{
			const char* data = container->LoadData(res, dataLenght);

			return const_cast<char*>(data);
		}

		it++;
	}

	// Nothing found
	dataLenght = 0;
	return NULL;
}

Resource * ResourceManager::GetResource(std::string name, GameModule * targetModule)
{
	return nullptr;
}

PointerList<Resource*> ResourceManager::GetSpriteResources(std::string spriteName, GameModule * targetModule)
{
	return PointerList<Resource*>();
}

PointerList<Resource*>* ResourceManager::CreateListOfResourcesFromXmlNodes(PointerList<XmlNode*> &resourceNodes)
{
	PointerList<Resource*>* resourceList = new PointerList<Resource*>();

	auto it = resourceNodes.GetContainer()->begin();

	while (it != resourceNodes.GetContainer()->end())
	{
		Resource* res = new Resource(this);

		XmlNode* node = (*it);

		res->Name = node->GetAttribute("name")->AttributeValue;

		auto resType = node->GetAttribute("type")->AttributeValue;

		if (strcmp(resType, "image") == 0)
		{
			res->Type = RES_IMG;
		}
		else if (strcmp(resType, "font") == 0)
		{
			res->Type = RES_FONT;
		}
		else if (strcmp(resType, "audio") == 0)
		{
			res->Type = RES_AUDIO;
		}

		res->Format = node->GetAttribute("format")->AttributeValue;

		resourceList->Add(res);

		it++;
	}

	return resourceList;
}

PointerList<ResourceContainer*>* ResourceManager::CreateListOfContainersFromXmlNodes(PointerList<XmlNode*>& containerNodes)
{
	PointerList<ResourceContainer*>* containersList = new PointerList<ResourceContainer*>();

	auto it = containerNodes.GetContainer()->begin();

	while (it != containerNodes.GetContainer()->end())
	{
		ResourceContainer* res = new ResourceContainer();

		XmlNode* node = (*it);

		res->Name = node->GetAttribute("name")->AttributeValue;
		
		auto resformat = node->GetAttribute("format")->AttributeValue;

		if (strcmp(resformat, "package") == 0)
		{
			res->ContainerType = CONTAINER_TYPE_PACKAGE;
		}
		else if (strcmp(resformat, "folder") == 0)
		{
			res->ContainerType = CONTAINER_TYPE_FOLDER;
		}
		
		containersList->Add(res);

		it++;
	}

	return containersList;
}
