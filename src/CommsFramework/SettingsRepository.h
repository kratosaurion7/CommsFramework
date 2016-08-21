#pragma once

#include <string>
#include <functional>
#include "PointerList.h"

#include "PointerList.h"
#include "Pair.h"

class SettingsRepository
{
public:
    static SettingsRepository* GetInstance();

    char* Get(std::string name);

    PointerList<char*>* GetWhere(std::function<bool(std::string)> predicate);

    void Register(std::string name, char* value);

    void ReadFromXml(std::string filePath);

protected:
    PointerList<Pair<std::string, char*>*>* SettingsList;

private:
    SettingsRepository();
    ~SettingsRepository();

    
    static SettingsRepository* _instance;
};