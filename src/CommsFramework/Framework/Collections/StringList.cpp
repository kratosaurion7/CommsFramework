#include "StringList.h"

#include <stdio.h>
#include <fstream>

#include "IO/FileReader.h"

StringList::StringList() : BaseList()
{
}


StringList::~StringList()
{
}

void StringList::Read(std::string fileName, char delimiter)
{
    std::fstream stream(fileName, std::ios::in);

    int count = 64;
    std::string* newString = new std::string();
    char buf[64];
    
    while (true)
    {
        stream.getline(buf, count, delimiter);

        newString->append(buf);

        if (strlen(buf) < count)
        {
            this->Add(newString);
        }
    }
}

void StringList::Read(FILE* fromFile, char delimiter)
{
}

void StringList::ReadLines(std::string fileName)
{
    FileReader fr(fileName);

    std::string* textLine = fr.NextLine();

    while (textLine != NULL)
    {
        this->Add(textLine);
    }
}

void StringList::ReadLines(FILE* fromFile)
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
