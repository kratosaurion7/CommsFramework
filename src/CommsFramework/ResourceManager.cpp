#include "ResourceManager.h"

#include "Resource.h"

#include "XmlReader.h"

ResourceManager::ResourceManager(std::string configFile)
{
    configFileLocation = configFile;

    secondaryConfigFiles = new BaseList<std::string>();
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::ParseConfigFiles()
{
    auto nextConfigFile = configFileLocation;

    bool hasNextConfig = true;

    while (hasNextConfig)
    {
        XmlReader rdr;

        rdr.LoadFile(nextConfigFile.c_str());

        auto resNodes = rdr.GetNodes("resource");

        auto it = resNodes->GetContainer()->begin();

        while (it != resNodes->GetContainer()->end())
        {
            Resource* res = new Resource();
            
            XmlNode* node = (*it);
            
        }

        auto containers = rdr.GetNodes("container");

        auto subConfigs = rdr.GetNodes("config");
    }

}
