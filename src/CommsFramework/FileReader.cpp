#include "FileReader.h"

#include <stdio.h>

#include <string>
#include <string.h>

#define READ_BLOCK_SIZE 128

FileReader::FileReader()
{
    fileStream = new std::fstream();
}

FileReader::FileReader(std::string filePath)
{
    fileStream = new std::fstream();
    fileStream->open(filePath, std::ios::in);
}

FileReader::~FileReader()
{
    if (fileStream != NULL)
        fileStream->close();

    delete(fileStream);
}

void FileReader::OpenFile(char* fileName)
{
    errno = 0;

    fileStream->open(fileName, std::ios::in | std::ios::binary);

    if (errno != 0)
    {
        printf("%s", strerror(errno));
    }
}

void FileReader::OpenFile(const char* fileName)
{
    errno = 0;

    fileStream->open(fileName, std::ios::in | std::ios::binary);

    if (errno != 0)
    {
        printf("%s", strerror(errno));
    }
}

FileContents* FileReader::GetFileContents(bool ensureNullTerminated)
{
    if (fileStream == NULL || !fileStream->good())
        return NULL;

    int fileSize = GetFileSize();

    auto newContent = new char[fileSize + 1];

    fileStream->read(newContent, fileSize);

    FileContents *fileContents = new FileContents();
    fileContents->fileSize = fileSize;
    if (ensureNullTerminated)
    {
        newContent[fileSize] = '\0';
    }
    fileContents->buffer = newContent;

    return fileContents;
}

std::string* FileReader::ReadChars(int count)
{
    char* buf = new char[count];
    fileStream->get(buf, count);

    return new std::string(buf);
}

std::string* FileReader::NextLine()
{
    char* buf = new char[1024];
    fileStream->getline(buf, 1024);

    if (fileStream->fail()) // Return null when file's end
        return NULL;

    return new std::string(buf);
}

void FileReader::ResetCursor()
{
    fileStream->seekp(0);
}

void FileReader::Close()
{
    if (fileStream != NULL)
        fileStream->close();
}
void FileReader::DumpFile(std::string outFileName)
{
    fileStream->seekg(0, std::ios_base::beg);

    std::ofstream outStream = std::ofstream(outFileName.c_str(), std::ofstream::out | std::ofstream::binary);

    int fileSize = GetFileSize();

    char* contents = new char[fileSize];

    fileStream->read(contents, fileSize);

    outStream.write(contents, fileSize);

    delete[] contents;

    outStream.close();

    fileStream->seekg(0, std::ios_base::beg);
}

int FileReader::GetFileSize()
{
    int fileSize = 0;

    if (fileStream->good())
    {
        int currentPos = fileStream->tellg();

        fileStream->seekg(0, std::ios::end);

        fileSize = fileStream->tellg();

        fileStream->seekg(currentPos);
    }

    return fileSize;
}

FileContents::FileContents()
{
}

FileContents::~FileContents()
{
    delete(buffer);
}
