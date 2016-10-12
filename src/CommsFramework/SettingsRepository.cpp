#include "SettingsRepository.h"

#include <cassert>

#include "XmlReader.h"

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
    
    assert(false);

    return NULL;
}

float SettingsRepository::GetFloat(std::string name)
{
    char* data = this->Get(name);

    if (data == NULL)
    {
        return 0;
    }

    float result = atof(data);

    return result;
}

int SettingsRepository::GetInt(std::string name)
{
    char* data = this->Get(name);

    if (data == NULL)
    {
        return 0;
    }

    int result = atoi(data);

    return result;
}

PointerList<char*>* SettingsRepository::GetWhere(std::function<bool(std::string)> predicate)
{
    PointerList<char*>* retValues = new PointerList<char*>();

    for (Pair<std::string, char*>* val : *this->SettingsList->GetContainer())
    {
        if (predicate(val->Item1))
        {
            retValues->Add(val->Item2);
        }
    }

    return retValues;
}

void SettingsRepository::Register(std::string name, char* value)
{
    Pair<std::string, char*>* newItem = new Pair<std::string, char*>();
    newItem->Item1 = name;
    newItem->Item2 = value;
    
    this->SettingsList->Add(newItem);
}

void SettingsRepository::ReadFromXml(std::string filePath)
{
    XmlReader settingsReader = XmlReader();
    settingsReader.LoadFile(filePath);

    auto settingNodes = settingsReader.FindNode("settings")->GetChildNodes();

    auto it = ITBEGIN(settingNodes);
    while (it != ITEND(settingNodes))
    {
        XmlNode* settingNode = *it;
        
        std::string settingName = settingNode->NodeName();
        char* settingValue = new char[settingNode->Contents().length()];
        strcpy(settingValue, settingNode->Contents().c_str());
        
        this->Register(settingName, settingValue);

        it++;
    }
}
