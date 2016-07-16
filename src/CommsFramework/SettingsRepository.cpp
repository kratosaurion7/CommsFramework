#include "SettingsRepository.h"

SettingsRepository* SettingsRepository::_instance = NULL;

SettingsRepository::SettingsRepository()
{
    this->SettingsList = new PointerList<Pair<std::string, char*>*>();
}

SettingsRepository::~SettingsRepository()
{
    this->SettingsList->Release();
    delete(this->SettingsList);
}

SettingsRepository* SettingsRepository::GetInstance()
{
    if (_instance == NULL)
    {
        _instance = new SettingsRepository();
    }

    return _instance;
}

char* SettingsRepository::Get(std::string name)
{
    for (Pair<std::string, char*>* val : *this->SettingsList->GetContainer())
    {
        if (val->Item1 == name)
        {
            return val->Item2;
        }
    }
}

void SettingsRepository::Register(std::string name, char* value)
{
    Pair<std::string, char*>* newItem = new Pair<std::string, char*>();
    newItem->Item1 = name;
    newItem->Item2 = value;

    this->SettingsList->Add(newItem);
}