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
#include "SpriteDescriptor.h"

#include "SpriteAnimation.h"
#include "BaseSprite.h"

class Resource;
class GameModule;
class ResourceContainer;
class SpriteDescriptor;
class BaseSprite;
class SpriteAnimation;

struct ResourceManagerInitParams {

    std::string AssetRootFolder;

    std::string ConfigFileLocation;

    static ResourceManagerInitParams* GetDefaultParams();
};

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void Init(ResourceManagerInitParams* initParams);

    void Load();

    void ParseConfigFiles();

    std::string PathToAssetsFolder;

    std::string configFileLocation;

    Resource* GetResource(std::string name, GameModule* targetModule = NULL);

    PointerList<SpriteAnimation*>* GetAnimationsForSprite(BaseSprite* sprite);

    //PointerList<Resource*>* GetSpriteResources(std::string spriteName, GameModule* targetModule = NULL);

    PointerList<Resource*>* Resources;

    PointerList<SpriteDescriptor*>* SpritesInfo;

    char* GetResourceDataFromStore(Resource* res, int& dataLenght, GameModule* targetModule = NULL);

private:
    ResourceManagerInitParams* startingParams;

    BaseList<std::string>* secondaryConfigFiles;

    void SetupSprites();

    PointerList<GameModule*>* Modules;
    PointerList<ResourceContainer*>* ResourceContainers;

    PointerList<Resource*>* CreateListOfResourcesFromXmlNodes(PointerList<XmlNode*> &resourceNodes);
    PointerList<ResourceContainer*>* CreateListOfContainersFromXmlNodes(PointerList<XmlNode*> &resourceNodes);

    PointerList<SpriteDescriptor*>* CreateSpritesFromXmlNodes(PointerList<XmlNode*> &spriteNodes);

};

