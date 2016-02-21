#include "FileSave.h"

#include "GenType.h"

FileSave::FileSave()
{
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
    
    int* newValue;
    *newValue = value;
    newVal->Value = newValue;

    Pair<KEYTYPE, GenType*>* newItem = new Pair<KEYTYPE, GenType*>(name, newVal);

    list->Add(newItem);
}

void FileSave::AddBool(KEYTYPE name, bool value)
{
    GenType* newVal = new GenType();
    newVal->ValueType = GenType::SUPPORTED_TYPES::BOOL;

    bool* newValue;
    *newValue = value;
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
}

void FileSave::SaveToFile(FILE * filePath)
{
}

FileSave* FileSave::LoadFromFile(std::string filePath)
{
    return nullptr;
}

FileSave* FileSave::LoadFromFile(FILE * file)
{
    return nullptr;
}
