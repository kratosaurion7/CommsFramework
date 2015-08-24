#include "ResourceManager.h"

#include "Resource.h"
#include "PointerList.h"

#include <queue>

#include "XmlReader.h"

#include "Utilities.h"

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

    SetupSprites();
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

            if (module == NULL)
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
    auto it = Resources->GetContainer()->begin();
    while (it != Resources->GetContainer()->end())
    {
        Resource* res = (*it);

        if (strcmp(res->Name.c_str(), name.c_str()) == 0)
        {
            return res;
        }

        it++;
    }

    return NULL;
}

PointerList<Resource*>* ResourceManager::GetSpriteResources(std::string spriteName, GameModule * targetModule)
{
    //PointerList<Resource*>* spriteResources = new PointerList<Resource*>();

    auto it = SpritesInfo->GetContainer()->begin();
    while (it != SpritesInfo->GetContainer()->end())
    {
        SpriteDescriptor* item = (*it);

        if (strcmp(item->SpriteName.c_str(), spriteName.c_str()) == 0)
        {
            return item->FrameResources;
        }

        it++;
    }

    return NULL;
}

void ResourceManager::SetupSprites()
{
    auto it = SpritesInfo->GetContainer()->begin();
    while (it != SpritesInfo->GetContainer()->end())
    {
        SpriteDescriptor* item = (*it);

        if (item->Frames->Count() > 0)
        {
            // Look at each frames and get the resource for each
            auto framesIterator = item->Frames->GetContainer()->begin();
            while (framesIterator != item->Frames->GetContainer()->end())
            {
                std::string frameName = (*framesIterator);

                Resource* res = GetResource(frameName);

                item->FrameResources->Add(res);

                framesIterator++;
            }
        }

        if (item->FrameLists->Count() > 0)
        {
            // Look at the framelists and generate resources

        }

        it++;
    }
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

        char* nameAttribute = node->GetAttribute("name").AttributeValue;

        if (nameAttribute == NULL)
        {
            // TODO : Add feedback
            break;
        }

        res->Name = nameAttribute;

        auto resformat = node->GetAttribute("format").AttributeValue;

        if (resformat != NULL)
        {
            if (strcmp(resformat, "package") == 0)
            {
                res->ContainerType = CONTAINER_TYPE_PACKAGE;
            }
            else if (strcmp(resformat, "folder") == 0)
            {
                res->ContainerType = CONTAINER_TYPE_FOLDER;
            }
            else
            {
                res->ContainerType = CONTAINER_TYPE_PACKAGE;
            }
        }
        else
        {
            // TODO : Get default from somewhere
            res->ContainerType = CONTAINER_TYPE_PACKAGE;
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

        char* spriteNameAttribute = node->GetAttribute("name").AttributeValue;
        if (spriteNameAttribute == NULL)
        {
            // Sprite without names are a NO NO.
            // TODO : Log something to let the user know this sprite will not be created.
            break;
        }

        newDescriptor->SpriteName = spriteNameAttribute;

        auto posNode = node->GetNode("position");
        if (posNode != NULL)
        {
            auto posX = SafeCharToFloat(posNode->GetAttribute("X").AttributeValue);
            auto posY = SafeCharToFloat(posNode->GetAttribute("Y").AttributeValue);
            newDescriptor->position = new FPosition(posX, posY);
        }
        else
        {
            // TODO : Get default from somewhere
            int posX = 0;
            int posY = 0;

            newDescriptor->position = new FPosition(posX, posY);
        }
        int i = 5;
        auto sizeNode = node->GetNode("size");
        if (sizeNode != NULL)
        {
            auto sizeH = SafeCharToFloat(sizeNode->GetAttribute("Height").AttributeValue, 1);
            auto sizeW = SafeCharToFloat(sizeNode->GetAttribute("Width").AttributeValue, 1);
            newDescriptor->size = new FSize(sizeH, sizeW);
        }
        else
        {
            int sizeH = 1;
            int sizeW = 1;
            newDescriptor->size = new FSize(sizeH, sizeW);
        }

        auto spriteFrames = node->GetNodes("frame");
        if (spriteFrames != NULL)
        {
            auto spriteFramesIterator = spriteFrames->GetContainer()->begin();
            while (spriteFramesIterator != spriteFrames->GetContainer()->end())
            {
                XmlNode* frameNode = (*spriteFramesIterator);

                char* idAttribute = frameNode->GetAttribute("Id").AttributeValue;
                if (idAttribute != NULL)
                {
                    // If the frame does not have an Id attribute to link to a resource, do not add the frame.
                    std::string frameId = frameNode->GetAttribute("Id").AttributeValue;

                    newDescriptor->Frames->Add(frameId);
                }

                spriteFramesIterator++;
            }
        }


        auto spriteFramelists = node->GetNodes("framelist");
        if (spriteFramelists != NULL)
        {
            auto framelistsIterator = spriteFramelists->GetContainer()->begin();
            while (framelistsIterator != spriteFramelists->GetContainer()->end())
            {
                XmlNode* frameListNode = (*framelistsIterator);

                Framelist* spriteFramelist = new Framelist();

                char* startAttribute = frameListNode->GetAttribute("start").AttributeValue;
                char* endAttribute = frameListNode->GetAttribute("end").AttributeValue;
                char* stepAttribute = frameListNode->GetAttribute("step").AttributeValue;
                char* patternAttribute = frameListNode->GetAttribute("pattern").AttributeValue;

                if (startAttribute == NULL || endAttribute == NULL || stepAttribute == NULL || patternAttribute == NULL)
                {
                    // Do not even try to create a framelist with missing values.
                    break;
                }

                spriteFramelist->startIndex = atoi(frameListNode->GetAttribute("start").AttributeValue);
                spriteFramelist->endIndex = atoi(frameListNode->GetAttribute("end").AttributeValue);
                spriteFramelist->step = atoi(frameListNode->GetAttribute("step").AttributeValue);
                spriteFramelist->pattern = frameListNode->GetAttribute("pattern").AttributeValue;

                newDescriptor->FrameLists->Add(spriteFramelist);

                framelistsIterator++;
            }
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
