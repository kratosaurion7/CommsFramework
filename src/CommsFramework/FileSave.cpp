#include "FileSave.h"

#include <cstdio>

#include "GenType.h"
#include "XFile.h"
#include "FileReader.h"
#include "BitHelper.h"

FileSave::FileSave()
{
    FileSaveVersion = V1;
    list = new BaseList<Pair<std::string, GenType*>*>();
}

FileSave::~FileSave()
{
    if (list != NULL)
    {
        list->Clear();
        delete(list);
    }
}

void FileSave::AddString(KEYTYPE name, std::string* value)
{
    GenType* newVal = new GenType();
    newVal->ValueType = GenType::SUPPORTED_TYPES::STRING;
    newVal->Value = value;

    Pair<KEYTYPE, GenType*>* newItem = new Pair<KEYTYPE, GenType*>(name, newVal);

    list->Add(newItem);
}

void FileSave::AddNumber(KEYTYPE name, int value)
{
    GenType* newVal = new GenType();
    newVal->ValueType = GenType::SUPPORTED_TYPES::INT32;
    
    newVal->Value = (void*)value;

    Pair<KEYTYPE, GenType*>* newItem = new Pair<KEYTYPE, GenType*>(name, newVal);

    list->Add(newItem);
}

void FileSave::AddBool(KEYTYPE name, bool value)
{
    GenType* newVal = new GenType();
    newVal->ValueType = GenType::SUPPORTED_TYPES::BOOL;

    newVal->Value = (void*)value;

    Pair<KEYTYPE, GenType*>* newItem = new Pair<KEYTYPE, GenType*>(name, newVal);

    list->Add(newItem);
}

void FileSave::AddData(KEYTYPE name, char* data, int length)
{
    GenType* newVal = new GenType();
    newVal->ValueType = GenType::SUPPORTED_TYPES::DATA;

    newVal->Value = data;
    newVal->ValueLength = length;

    Pair<KEYTYPE, GenType*>* newItem = new Pair<KEYTYPE, GenType*>(name, newVal);

    list->Add(newItem);
}

std::string* FileSave::GetString(KEYTYPE name)
{
    Pair<std::string, GenType*>* foundItem = list->GetBy([name](Pair<KEYTYPE, GenType*>* item) {
        if (item->Item1 == name)
            return item;
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::STRING)
        {
            return (std::string*)foundItem->Item2->Value;
        }
    }
    else
    {
        return NULL;
    }
}

int FileSave::GetNumber(KEYTYPE name)
{
    Pair<std::string, GenType*>* foundItem = list->GetBy([name](Pair<KEYTYPE, GenType*>* item) {
        if (item->Item1 == name)
            return item;
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::INT32)
        {
            return (int)foundItem->Item2->Value;
        }
    }
    else
    {
        return NULL;
    }
}

bool FileSave::GetBool(KEYTYPE name)
{
    Pair<std::string, GenType*>* foundItem = list->GetBy([name](Pair<KEYTYPE, GenType*>* item) {
        if (item->Item1 == name)
            return item;
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::BOOL)
        {
            return (bool)foundItem->Item2->Value;
        }
    }

    return NULL;
}

char* FileSave::GetData(KEYTYPE name, int & outLength)
{
    Pair<std::string, GenType*>* foundItem = list->GetBy([name](Pair<KEYTYPE, GenType*>* item) {
        if (item->Item1 == name)
            return item;
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::DATA)
        {
            return (char*)foundItem->Item2->Value;
        }
    }

    return NULL;
}

void FileSave::SaveToFile(std::string filePath)
{
    XFile saveFile(filePath);
    saveFile.OpenCreate();

    if (saveFile.FileValid)
    {
        int dataSize = 0;
        const char* data = SaveToDataString(dataSize);

        saveFile.Write((char*)data, dataSize);
        // TODO : Flush file asap
        delete(data);
    }
}

void FileSave::SaveToFile(FILE* filePath)
{
}

const char* FileSave::SaveToDataString(int& outLength)
{
    std::string* outString = new std::string();

    outString->append(std::to_string(FileSaveVersion));

    auto it = list->GetContainer()->begin();
    while (it != list->GetContainer()->end())
    {
        Pair<std::string, GenType*>* element = (*it);

        outString->append(std::to_string(element->Item2->ValueType));
        outString->append(element->Item1.c_str(), element->Item1.length() + 1);

        switch (element->Item2->ValueType)
        {
            case GenType::SUPPORTED_TYPES::BOOL:
            {
                bool value = (bool)element->Item2->Value;

                int numValue = (int)value;

                std::string serializedValue = std::to_string(numValue);
                outString->append(serializedValue.c_str(), serializedValue.length() + 1);

                break;
            }
            case GenType::SUPPORTED_TYPES::DATA: 
            {
                char* value = (char*)element->Item2->Value;

                std::string dataLengthString = std::to_string(element->Item2->ValueLength);
                
                unsigned char* sizeString = IntToBytes(element->Item2->ValueLength);
                outString->append((char*)sizeString, 4);
                outString->append(value, element->Item2->ValueLength + 1);

                break;
            }
            case GenType::SUPPORTED_TYPES::INT32:
            {
                int value = (int)element->Item2->Value;

                std::string serializedValue = std::to_string(value);
                outString->append(serializedValue.c_str(), serializedValue.length() + 1);

                break;
            }
            case GenType::SUPPORTED_TYPES::STRING:
            {
                std::string* value = (std::string*)element->Item2->Value;

                outString->append(value->c_str(), value->length() + 1);

                break;
            }
        }

        it++;
    }

    outLength = outString->length();
    return outString->c_str();
}

FileSave* FileSave::LoadFromFile(std::string filePath)
{
    FileSave* loadedSave = NULL;

    XFile inFile(filePath);
    inFile.Open();

    if (inFile.FileValid)
    {
        std::ifstream* fs = inFile.GetFileStream();
        
        if (fs->good())
        {
            FileSave::SAVE_VERSION fileVersion = FileSave::SAVE_VERSION::BAD;
            char versionHeader[1];
            fs->read(versionHeader, 1);

            switch (versionHeader[0])
            {
                case FileSave::SAVE_VERSION::V1:
                {
                    loadedSave = FileSave::ProcessV1SaveFile(fs);

                    break;
                }
                default:
                {
                    break;
                }
            }
        }

    }

    return loadedSave;
}

FileSave* FileSave::LoadFromFile(FILE* file)
{
    return nullptr;
}

FileSave* FileSave::ProcessV1SaveFile(std::ifstream* stream)
{
    FileSave* newSave = new FileSave();

    while (!stream->eof())
    {
        // Read type byte
        char typeByte[1];
        stream->read(typeByte, 1);

        char* elementName = new char[MAX_KEY_NAME];
        stream->getline(elementName, MAX_KEY_NAME, '\0');

        switch (typeByte[0])
        {
            case GenType::SUPPORTED_TYPES::BOOL:
            {
                char val[1];
                stream->read(val, 1);

                bool value = val[0];

                newSave->AddBool(elementName, value);

                break;
            }
            case GenType::SUPPORTED_TYPES::DATA:
            {
                
                


                break;
            }
            case GenType::SUPPORTED_TYPES::INT32:
            {
                break;
            }
            case GenType::SUPPORTED_TYPES::STRING:
            {
                break;
            }
            default:
                break;
        }

        return NULL;
    }

}
