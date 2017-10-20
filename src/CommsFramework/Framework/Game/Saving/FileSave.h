#pragma once

class GenType;

#include <cstdio>
#include <string>
#include <string.h>

#include "BaseList.h"
#include "Pair.h"

#define KEYTYPE std::string
#define MAX_KEY_NAME 256

/*
    The FileSave class is used to persist data from an appplication.

    The format is made in a way that the container has an understanding of the 
    types of the values it contains so that when the file is loaded, each value
    can be returned as the right type.

    Each file's first byte is the version number of the save format so that if 
    the format change, it can remain backward compatible with the previous
    versions.
*/
class FileSave
{
public:
    FileSave();
    ~FileSave();

    enum SAVE_VERSION
    {
        V1 = 0,

        BAD = 999999,
    } FileSaveVersion;

    void AddString(KEYTYPE name, std::string* value);
    void AddNumber(KEYTYPE name, int value);
    void AddBool(KEYTYPE name, bool value);
    void AddData(KEYTYPE name, char* data, int length);

    std::string* GetString(KEYTYPE name);
    int GetNumber(KEYTYPE name);
    bool GetBool(KEYTYPE name);
    char* GetData(KEYTYPE name, int& outLength);

    BaseList<KEYTYPE>* GetAllKeys();
    
    GenType* GetGenericValue(KEYTYPE key);

    virtual void SaveToFile(std::string filePath);
    virtual void SaveToFile(FILE* filePath);

    const char* SaveToDataString(int& outLength);

    static FileSave* LoadFromFile(std::string filePath);
    static FileSave* LoadFromFile(FILE* file);

private:
    BaseList<Pair<KEYTYPE, GenType*>*>* list;

    static FileSave* ProcessV1SaveFile(std::ifstream* stream);
};

