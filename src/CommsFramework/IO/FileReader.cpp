#include "FileReader.h"

#include <stdio.h>

#include <string>

#define READ_BLOCK_SIZE 128

FileReader::FileReader()
{
    file = NULL;
    contents = NULL;

    contents = new std::string();
};

FileReader::~FileReader()
{
    if (file != NULL)
        fclose(file);
    
};

void FileReader::OpenFile(char* fileName, FileAccessFlags access)
{
    char* mode = TranslateAccessFlag(access);
    file = fopen(fileName, mode);
    
    if (file == NULL)
        return; // TODO : Return an error enum value ?
};


FileContents* FileReader::GetFileContents()
{
    char buf[READ_BLOCK_SIZE];

    if (file == NULL)
        return NULL;

    while (!feof(file))
    {
        if (fgets(buf, READ_BLOCK_SIZE, file) == NULL)
            break;

        contents->append(buf);
    }

    FileContents *fileContents = new FileContents();
    fileContents->buffer = contents->c_str();
    fileContents->fileSize = contents->size();

    return fileContents;
};

char* FileReader::TranslateAccessFlag(FileAccessFlags flag)
{
    switch (flag)
    {
        case READ:
            return "r";
            break;
        case WRITE:
            return "w";
            break;
        case READWRITE:
            return "r+"; // Or maybe use w+ to auto create the file.
            break;
        default:
            return "r";
            break;
    }
};

