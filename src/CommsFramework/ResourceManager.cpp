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
	SpritesInfo = new PointerList<SpriteDescriptor*>();

    PathToAssetsFolder = "assets\\"; // Temp default value
	startingParams = NULL;
}

ResourceManager::~ResourceManager()
{
    delete(secondaryConfigFiles);
	
	delete(startingParams);

	SpritesInfo->Release();
	delete(SpritesInfo);

    Resources->Release();
    delete(Resources);

    ResourceContainers->Release();
    delete(ResourceContainers);

    Modules->Release();
    delete(Modules);
}

void ResourceManager::Init(ResourceManagerInitParams* initParams)
{
	configFileLocation = initParams->ConfigFileLocation;
	PathToAssetsFolder = initParams->AssetRootFolder;

	startingParams = initParams;

	ParseConfigFiles();
}

void ResourceManager::ParseConfigFiles()
{
	if (configFileLocation == "")
		return;

    std::string nextConfigFile = PathToAssetsFolder + configFileLocation;

    std::queue<std::string> configQueue;

	configQueue.push(nextConfigFile);

	while (strcmp(nextConfigFile.c_str(), "") != 0)
    {
        XmlReader rdr = XmlReader();

        rdr.LoadFile(nextConfigFile.c_str());

		PointerList<XmlNode*>* resNodes = rdr.GetNodes("resource");
		PointerList<Resource*>* newResources = CreateListOfResourcesFromXmlNodes(*resNodes);
		
		Resources->AddRange(newResources);

        XmlNode* rootNode = rdr.GetNode("config");
        XmlNodeAttribute moduleNameAttr = rootNode->GetAttribute("ModuleName");

        if (moduleNameAttr.AttributeName != NULL)
        {
            GameModule* module = NULL;
            
            for (int i = 0; i < Modules->Count(); i++)
            {
                GameModule* testModule = Modules->Get(i);

                if (testModule->ModuleName == moduleNameAttr.AttributeName)
                {
                    module = testModule;
                }
            }

            if(module == NULL)
                module = new GameModule();

            module->ModuleName = moduleNameAttr.AttributeValue;
            
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

            std::string combinedPath = PathToAssetsFolder + element->GetAttribute("path").AttributeValue;
			std::string configFileName = element->GetAttribute("path").AttributeValue;

			configQueue.push(combinedPath);
			secondaryConfigFiles->Add(configFileName); // Add the config file name NOT prepended by the assets root folder path.

			it++;
		}
        
		PointerList<XmlNode*>* containers = rdr.GetNodes("container");
		PointerList<ResourceContainer*>* newContainers = CreateListOfContainersFromXmlNodes(*containers);

		ResourceContainers->AddRange(newContainers);

		delete(newContainers);

		PointerList<XmlNode*>* spriteNodes = rdr.GetNodes("sprite");
		PointerList<SpriteDescriptor*>* newSprites = CreateSpritesFromXmlNodes(*spriteNodes);

		SpritesInfo->AddRange(newSprites);

		delete(newSprites);

		configQueue.pop();

		if (configQueue.empty())
		{
			nextConfigFile = "";
		}
		else 
		{
			nextConfigFile = configQueue.front();
		}

		spriteNodes->Release();
		delete(spriteNodes);
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

	if (targetModule != NULL)
	{
		for (int i = 0; i < Modules->Count();i++)
		{
			GameModule* nextModule = Modules->Get(i);

			if (strcmp(nextModule->ModuleName.c_str(), targetModule->ModuleName.c_str()) == 0)
			{
				moduleOfResource = nextModule;
				break;
			}
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

		res->Name = node->GetAttribute("name").AttributeValue;

		auto resType = node->GetAttribute("type").AttributeValue;

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

		res->Format = node->GetAttribute("format").AttributeValue;

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

		res->Name = node->GetAttribute("name").AttributeValue;
		
		auto resformat = node->GetAttribute("format").AttributeValue;

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

PointerList<SpriteDescriptor*>* ResourceManager::CreateSpritesFromXmlNodes(PointerList<XmlNode*>& spriteNodes)
{
	PointerList<SpriteDescriptor*>* descriptors = new PointerList<SpriteDescriptor*>();

	auto it = spriteNodes.GetContainer()->begin();

	while (it != spriteNodes.GetContainer()->end())
	{
		XmlNode* node = (*it);

		SpriteDescriptor* newDescriptor = new SpriteDescriptor();
		
		auto posNode = node->GetNode("position");
		auto posX = atof(posNode->GetAttribute("X").AttributeValue);
		auto posY = atof(posNode->GetAttribute("Y").AttributeValue);
		newDescriptor->position = new FPosition(posX, posY);

		auto sizeNode = node->GetNode("size");
		auto sizeH = atof(sizeNode->GetAttribute("Height").AttributeValue);
		auto sizeW = atof(sizeNode->GetAttribute("Width").AttributeValue);
		newDescriptor->size = new FSize(sizeH, sizeW);

		auto spriteFrames = node->GetNodes("frame");

		auto spriteFramesIterator = spriteFrames->GetContainer()->begin();
		while (spriteFramesIterator != spriteFrames->GetContainer()->end())
		{
			XmlNode* frameNode = (*spriteFramesIterator);

			std::string frameId = frameNode->GetAttribute("Id").AttributeValue;

			newDescriptor->Frames->Add(frameId);

			spriteFramesIterator++;
		}

		auto spriteFramelists = node->GetNodes("framelist");

		auto framelistsIterator = spriteFramelists->GetContainer()->begin();
		while (framelistsIterator != spriteFramelists->GetContainer()->end())
		{
			XmlNode* frameListNode = (*framelistsIterator);

			Framelist* spriteFramelist = new Framelist();
			spriteFramelist->startIndex = atoi(frameListNode->GetAttribute("start").AttributeValue);
			spriteFramelist->endIndex = atoi(frameListNode->GetAttribute("end").AttributeValue);
			spriteFramelist->step = atoi(frameListNode->GetAttribute("step").AttributeValue);
			spriteFramelist->pattern = frameListNode->GetAttribute("pattern").AttributeValue;

			newDescriptor->FrameLists->Add(spriteFramelist);

			framelistsIterator++;
		}

		descriptors->Add(newDescriptor);

		spriteFrames->Release();
		delete(spriteFrames);

		spriteFramelists->Release();
		delete(spriteFramelists);

		delete(sizeNode);
		delete(posNode);

		it++;
	}

	return descriptors;
}

ResourceManagerInitParams * ResourceManagerInitParams::GetDefaultParams()
{
	ResourceManagerInitParams* ret = new ResourceManagerInitParams();
	ret->AssetRootFolder = "Assets\\";
	ret->ConfigFileLocation = "config_file_example.xml";

	return ret;
}
