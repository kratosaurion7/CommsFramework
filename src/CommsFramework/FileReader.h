#pragma once

#include <string>
#include <stdio.h>

enum FileAccessFlags
{
    READ,
    WRITE,
    READWRITE
};

struct FileContents
{
    const char* buffer;
    int fileSize;
};

class FileReader
{
public:
    FileReader();
    ~FileReader();

    void OpenFile(char* fileName, FileAccessFlags access);

    FileContents* GetFileContents();
    

private:
    FILE* file;

    std::string* contents;

    char* TranslateAccessFlag(FileAccessFlags flag);
};

