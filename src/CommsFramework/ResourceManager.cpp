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
        }

        auto containers = rdr.GetNodes("container");

        auto subConfigs = rdr.GetNodes("config");
    }

}
