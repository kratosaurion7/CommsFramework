#include "ConfigurationManager.h"

#include "XmlReader.h"
#include "XDirectory.h"
#include "XFile.h"


ConfigurationManager::ConfigurationManager()
{
    this->SettingsList = new PointerList<Pair<std::string, char*>*>();
}


ConfigurationManager::~ConfigurationManager()
{
}

void ConfigurationManager::LoadConfig()
{
    XmlReader settingsReader = XmlReader();
    settingsReader.LoadFile(defaultConfigFileName);

    this->ExtractConfigFromFile(&settingsReader, this->SettingsList);

}

void ConfigurationManager::LoadConfig(std::string rootConfigFilePath, std::string settingsRootNodeName)
{
    XmlReader settingsReader = XmlReader();
    settingsReader.LoadFile(rootConfigFilePath);

    auto settingNodes = settingsReader.FindNode(settingsRootNodeName)->GetChildNodes();

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

char* ConfigurationManager::Get(std::string settingName)
{
    for (Pair<std::string, char*>* val : *this->SettingsList->GetContainer())
    {
        if (val->Item1 == settingName)
        {
            return val->Item2;
        }
    }

    fprintf(stderr, "Setting %s not found.\n", settingName.c_str());

    return NULL;
}

PointerList<char*>* ConfigurationManager::GetWhere(std::function<bool(std::string)> predicate)
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

int ConfigurationManager::GetInt(std::string settingName)
{
    char* data = this->Get(settingName);

    if (data == NULL)
    {
        return 0;
    }

    int result = atoi(data);

    return result;
}

float ConfigurationManager::GetFloat(std::string settingName)
{
    char* data = this->Get(settingName);

    if (data == NULL)
    {
        return 0;
    }

    float result = atof(data);

    return result;
}

bool ConfigurationManager::GetBool(std::string settingName)
{
    char* data = this->Get(settingName);

    if (data == NULL)
    {
        return 0;
    }

    int result = atoi(data);

    return result;
}

void ConfigurationManager::Register(std::string name, char* value)
{
    Pair<std::string, char*>* newItem = new Pair<std::string, char*>();
    newItem->Item1 = name;
    newItem->Item2 = value;

    this->SettingsList->Add(newItem);
}

void ConfigurationManager::ExtractConfigFromFile(XmlReader* fileReader, PointerList<Pair<std::string, char*>*>* list)
{
    auto rootSettingNode = fileReader->FindNode(defaultConfigNodeName);

    if (rootSettingNode == NULL)
        return; // No <settings> node

    auto settingNodes = rootSettingNode->GetChildNodes();

    auto it = ITBEGIN(settingNodes);
    while (it != ITEND(settingNodes))
    {
        XmlNode* settingNode = *it;

        std::string settingName = settingNode->NodeName();
        char* settingValue = new char[settingNode->Contents().length()];
        strcpy(settingValue, settingNode->Contents().c_str());

        // Creating a new pair here rather than going through the ::Register function.
        // Better for recursivity by using the 'list' parameter.
        Pair<std::string, char*>* newItem = new Pair<std::string, char*>();
        newItem->Item1 = settingName;
        newItem->Item2 = settingValue;

        list->Add(newItem);

        //this->Register(settingName, settingValue);

        it++;
    }

    auto linkedConfigFilesNodes = fileReader->GetNodes("link");

    auto link_it = ITBEGIN(linkedConfigFilesNodes);
    while (link_it != ITEND(linkedConfigFilesNodes))
    {
        XmlNode* linkNode = *link_it;

        // If there is a node linking to a config file, open the file and load the config
        std::string linkedFile = linkNode->GetAttribute("src").AttributeValue;

        if (linkedFile != "")
        {
            XmlReader linkedFileReader = XmlReader();
            linkedFileReader.LoadFile(linkedFile);

            ExtractConfigFromFile(&linkedFileReader, list);
        }

        // If there is a node linking to a directory, load all the xml files in the directory
        std::string linkedDirectory = linkNode->GetAttribute("dir").AttributeValue;
        std::string linkedDirFilePattern = linkNode->GetAttribute("pattern").AttributeValue;

        if (linkedDirectory != "" && linkedDirFilePattern != "")
        {
            XDirectory linkedDir = XDirectory(linkedDirectory);

            auto linkedDirFiles = linkedDir.GetFiles(true);

            auto linkedFileIt = ITBEGIN(linkedDirFiles);
            while (linkedFileIt != ITEND(linkedDirFiles))
            {
                XFile* file = *linkedFileIt;

                auto res = file->FileName.find(linkedDirFilePattern, 0);

                // If the file fits the pattern
                if (res != std::string::npos)
                {
                    XmlReader fileReader = XmlReader();
                    fileReader.LoadFile(file->FilePath);

                    ExtractConfigFromFile(&fileReader, list);
                }

                linkedFileIt++;
            }

            linkedDirFiles->Clear();
            delete(linkedDirFiles);
        }

        link_it++;
    }

}