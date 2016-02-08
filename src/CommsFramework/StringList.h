#pragma once

#include "BaseList.h"

#include <string>

class StringList : public BaseList<std::string*>
{
public:
    StringList();
    ~StringList();

    void Read(std::string fileName, std::string delimiter);
    void Read(FILE *fromFile, std::string delimiter);

    void ReadLines(std::string fileName);
    void ReadLines(FILE* fromFile);

    void Save(std::string fileName);
    void Save(FILE* toFile);

    void SaveLines(std::string fileName);
    void SaveLines(FILE* toFile);
};

