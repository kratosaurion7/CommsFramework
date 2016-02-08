#pragma once

#include "BaseList.h"

#include <string>
#include "BaseList.h"

class StringList : public BaseList<std::string*>
{
public:
    StringList();
    ~StringList();

    void Read(std::string fileName);
    void Read(FILE *fromFile);

    void ReadLines(std::string fileName);
    void ReadLines(FILE* fromFile);

    void Save(std::string fileName);
    void Save(FILE* toFile);

    void SaveLines(std::string fileName);
    void SaveLines(FILE* toFile);
};

