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

		return (Pair<std::string, GenType*>*)NULL; // Using the cast of NULL to help with the compiler deduced lambda return type.
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::STRING)
        {
            return (std::string*)foundItem->Item2->Value;
        }
		else
		{
			// Mismatched type
		}
    }

    return NULL;
}

int FileSave::GetNumber(KEYTYPE name)
{
    Pair<std::string, GenType*>* foundItem = list->GetBy([name](Pair<KEYTYPE, GenType*>* item) {
        if (item->Item1 == name)
            return item;

		return (Pair<std::string, GenType*>*)NULL; // Using the cast of NULL to help with the compiler deduced lambda return type.
	});

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::INT32)
        {
            return (int)foundItem->Item2->Value;
        }
		else
		{
			// Mismatched type
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

		return (Pair<std::string, GenType*>*)NULL; // Using the cast of NULL to help with the compiler deduced lambda return type.
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::BOOL)
        {
            return (bool)foundItem->Item2->Value;
        }
		else
		{
			// Mismatched type
		}
    }

    return NULL;
}

char* FileSave::GetData(KEYTYPE name, int & outLength)
{
    Pair<std::string, GenType*>* foundItem = list->GetBy([name](Pair<KEYTYPE, GenType*>* item) {
        if (item->Item1 == name)
            return item;

		return (Pair<std::string, GenType*>*)NULL; // Using the cast of NULL to help with the compiler deduced lambda return type.
    });

    if (foundItem != NULL)
    {
        if (foundItem->Item2->ValueType == GenType::SUPPORTED_TYPES::DATA)
        {
            return (char*)foundItem->Item2->Value;
        }
		else 
		{
			// Mismatched type
		}
    }

    return NULL;
}

BaseList<KEYTYPE>* FileSave::GetAllKeys()
{
    BaseList<KEYTYPE>* keys = new BaseList<KEYTYPE>();

    auto it = this->list->GetContainer()->begin();
    while (it != this->list->GetContainer()->end())
    {
        Pair<KEYTYPE, GenType*>* value = (*it);

        keys->Add(value->Item1);

        it++;
    }

    return keys;
}

GenType* FileSave::GetGenericValue(KEYTYPE key)
{
    auto it = this->list->GetContainer()->begin();
    while (it != this->list->GetContainer()->end())
    {
        Pair<KEYTYPE, GenType*>* value = (*it);

        if (value->Item1 == key)
        {
            return value->Item2;
        }

        it++;
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
            case GenType::SUPPORTED_TYPES::INT32:
            {
                int value = (int)element->Item2->Value;

                char* valueBytes = (char*)&(value);

                outString->append(valueBytes, 4);
                outString->append("\0", 1); // Somehow have to add the element null terminator delimiter by hand

                break;
            }
            case GenType::SUPPORTED_TYPES::BOOL:
            {
                bool value = (bool)element->Item2->Value;

                int numValue = (int)value;

                std::string serializedValue = std::to_string(numValue);
                outString->append(serializedValue.c_str(), serializedValue.length() + 1);

                break;
            }
            case GenType::SUPPORTED_TYPES::STRING:
            {
                std::string* value = (std::string*)element->Item2->Value;

                outString->append(value->c_str(), value->length() + 1);

                break;
            }
            case GenType::SUPPORTED_TYPES::DATA: 
            {
                char* value = (char*)element->Item2->Value;

                std::string dataLengthString = std::to_string(element->Item2->ValueLength);
                
                char* sizeString = (char*)&(element->Item2->ValueLength);
                outString->append(sizeString, 4);
                outString->append(value, element->Item2->ValueLength + 1);

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
    inFile.Open(FILE_OPEN_MODE::XFILE_READ, FILE_SHARE_MODE::XSHARE_READ);

    if (inFile.FileValid)
    {
        std::ifstream* fs = inFile.GetFileStream();
        //std::ifstream* fs = new std::ifstream("save.bin", std::ios_base::binary);

        auto tt = strerror(errno);

        if (fs->good())
        {
            FileSave::SAVE_VERSION fileVersion = FileSave::SAVE_VERSION::BAD;
            char versionHeader[1];
            fs->read(versionHeader, 1);

            // Using the trick of substracting the value of '0' (48) to convert from the version number string to it's int value. ex: '0' = int 48.
            FileSave::SAVE_VERSION x = (FileSave::SAVE_VERSION)(versionHeader[0] - '0');

            switch (x)
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

        switch (typeByte[0] - '0')
        {
            case GenType::SUPPORTED_TYPES::INT32:
            {
                char numberBytes[4];
                stream->read(numberBytes, 4);

                int number = *((int*)numberBytes);

                newSave->AddNumber(elementName, number);

                break;
            }
            case GenType::SUPPORTED_TYPES::BOOL:
            {
                char val[1];
                stream->read(val, 1);

                bool value = val[0] - '0';

                newSave->AddBool(elementName, value);

                break;
            }
            case GenType::SUPPORTED_TYPES::STRING:
            {
                char* inputString = new char[512]; // Implement safe max value ?
                stream->getline(inputString, 512, '\0');

                std::string* newStr = new std::string(inputString);

                newSave->AddString(elementName, newStr);

                break;
            }
            case GenType::SUPPORTED_TYPES::DATA:
            {
                char dataLen[4];
                stream->read(dataLen, 4);
                
                int len = *((int*)dataLen); // Convert 4 ints to a char

                char* data = new char[len];
                stream->read(data, len);

                newSave->AddData(elementName, data, len);

                break;
            }
            default:
                break;
        }

        char valueEndDelim[1];
        stream->read(valueEndDelim, 1);

        if (valueEndDelim[0] != '\0')
        {
            int i = 0;
        }
        
    }

    return newSave;
}
