#pragma once

class XmlReader;

#include <string>

#include "PointerList.h"
#include "Pair.h"

class ConfigurationManager
{
public:
    ConfigurationManager();
    ~ConfigurationManager();

    void LoadConfig();
    void LoadConfig(std::string rootConfigFilePath, std::string settingsRootNodeName = "settings");

    char* Get(std::string valueName);

    int GetInt(std::string valueName);

    float GetFloat(std::string valueName);

    bool GetBool(std::string valueName);

    void Register(std::string name, char* value);

protected:
    PointerList<Pair<std::string, char*>*> SettingsList;


private:
    std::string defaultConfigFileName = "config.xml";
    std::string defaultConfigNodeName = "settings";

    void ExtractConfigFromFile(XmlReader* fileReader, PointerList<Pair<std::string, char*>*>* list);
};