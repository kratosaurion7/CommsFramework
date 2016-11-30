#pragma once

class XmlReader;

#include <string>

#include "FluentConfigurationSetting.h"
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

    template<class T>
    FluentConfigurationSetting<T>* FindValue(std::string valueName);

    PointerList<char*>* GetWhere(std::function<bool(std::string)> predicate);

    int GetInt(std::string valueName);

    float GetFloat(std::string valueName);

    bool GetBool(std::string valueName);

    void Register(std::string name, char* value);

protected:
    PointerList<Pair<std::string, char*>*>* SettingsList;


private:
    std::string defaultConfigFileName = "config.xml";
    std::string defaultConfigNodeName = "settings";

    void ExtractConfigFromFile(XmlReader* fileReader, PointerList<Pair<std::string, char*>*>* list);
};

template<class T>
FluentConfigurationSetting<T>* ConfigurationManager::FindValue(std::string valueName)
{
    char* orig_value = this->Get(valueName);

    T* result = (T*)orig_value;

    FluentConfigurationSetting<T>* configurator = new FluentConfigurationSetting<T>(result);

    return configurator;
}
