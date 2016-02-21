#include "FileSave.h"

#include "GenType.h"
#include "XFile.h"

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
    
    int* newValue = NULL;
    newValue = &value;
    newVal->Value = newValue;

    Pair<KEYTYPE, GenType*>* newItem = new Pair<KEYTYPE, GenType*>(name, newVal);

    list->Add(newItem);
}

void FileSave::AddBool(KEYTYPE name, bool value)
{
    GenType* newVal = new GenType();
    newVal->ValueType = GenType::SUPPORTED_TYPES::BOOL;

    bool* newValue = NULL;
    newValue = &value;
    newVal->Value = newValue;

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
        outString->append(element->Item1);

        switch (element->Item2->ValueType)
        {
            case GenType::SUPPORTED_TYPES::BOOL:
            {
                bool value = element->Item2->Value;

                int numValue = (int)value;

                outString->append(std::to_string(numValue));

                break;
            }
            case GenType::SUPPORTED_TYPES::DATA: 
            {
                char* value = (char*)element->Item2->Value;

                outString->append(value, element->Item2->ValueLength);

                break;
            }
            case GenType::SUPPORTED_TYPES::INT32:
            {
                int value = (int)element->Item2->Value;

                outString->append(std::to_string(value));

                break;
            }
            case GenType::SUPPORTED_TYPES::STRING:
            {
                std::string* value = (std::string*)element->Item2->Value;

                outString->append(value->c_str());

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
    return nullptr;
}

FileSave* FileSave::LoadFromFile(FILE * file)
{
    return nullptr;
}
