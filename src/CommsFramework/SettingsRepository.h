#pragma once

#include <string>

#include "PointerList.h"
#include "Pair.h"

class SettingsRepository
{
public:
    static SettingsRepository* GetInstance();

    char* Get(std::string name);

    void Register(std::string name, char* value);

protected:
    PointerList<Pair<std::string, char*>*>* SettingsList;

private:
    SettingsRepository();
    ~SettingsRepository();

    
    static SettingsRepository* _instance;
};