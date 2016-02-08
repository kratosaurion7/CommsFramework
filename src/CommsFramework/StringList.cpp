#include "StringList.h"

#include <stdio.h>
#include <fstream>

#include "FileReader.h"

StringList::StringList() : BaseList()
{
}


StringList::~StringList()
{
}

void StringList::Read(std::string fileName, std::string delimiter)
{
    std::fstream stream(fileName, std::ios::in);

    int count = 64;
    char* buf;
    
    while (true)
    {
        stream.getline(buf, count, '\n');

        std::string* newLine = new std::string(buf);

        this->Add(newLine);
            break;
        
        
    }
}

void StringList::Read(FILE * fromFile, std::string delimiter)
{
}

void StringList::ReadLines(std::string fileName)
{
}

void StringList::ReadLines(FILE * fromFile)
{
}

void StringList::Save(std::string fileName)
{
}

void StringList::Save(FILE * toFile)
{
}

void StringList::SaveLines(std::string fileName)
{
}

void StringList::SaveLines(FILE * toFile)
{
}
