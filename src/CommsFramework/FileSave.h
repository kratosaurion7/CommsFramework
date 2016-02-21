#pragma once

class GenType;

#include <cstdio>
#include <string>

#include "BaseList.h"
#include "Pair.h"


#define KEYTYPE std::string

class FileSave
{
public:
    FileSave();
    ~FileSave();

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

    static FileSave* LoadFromFile(std::string filePath);
    static FileSave* LoadFromFile(FILE* file);

private:
    BaseList<Pair<std::string, GenType*>*>* list;
};

