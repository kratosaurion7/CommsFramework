#pragma once

class XmlReader;

#include <string>
#include <string.h>

#include "PointerList.h"
#include "Pair.h"

class ConfigurationManager
{
public:
    ConfigurationManager();
    ~ConfigurationManager();

    void LoadConfig();
    void LoadConfig(std::string rootConfigFilePath, std::string settingsRootNodeName = "settings");

    void Register(std::string name, char* value);

    char* Get(std::string valueName, char* defaultValue = NULL);

    PointerList<char*>* GetWhere(std::function<bool(std::string)> predicate);

    int GetInt(std::string valueName, int defaultValue = -1);

    float GetFloat(std::string valueName, float defaultValue = -1);

    bool GetBool(std::string valueName, bool defaultValue = false);

protected:
    PointerList<Pair<std::string, char*>*>* SettingsList;


private:
    const std::string defaultConfigFileName = "config.xml";
    const std::string defaultConfigNodeName = "settings";

    void ExtractConfigFromFile(XmlReader* fileReader, PointerList<Pair<std::string, char*>*>* list);
};