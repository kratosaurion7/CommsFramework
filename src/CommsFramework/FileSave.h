#pragma once

class GenType;

#include <cstdio>
#include <string>

#include "BaseList.h"
#include "Pair.h"

#define KEYTYPE std::string
#define MAX_KEY_NAME 256

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

    void SaveToFile(std::string filePath);
    void SaveToFile(FILE* filePath);

    const char* SaveToDataString(int& outLength);

    static FileSave* LoadFromFile(std::string filePath);
    static FileSave* LoadFromFile(FILE* file);

private:
    BaseList<Pair<std::string, GenType*>*>* list;

    static FileSave* ProcessV1SaveFile(std::ifstream* stream);
};

