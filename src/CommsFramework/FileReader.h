#pragma once

#include <string>
#include <stdio.h>

#include <fstream>

class FileContents
{
public:
    char* buffer;
    int fileSize;

    FileContents();
    ~FileContents();
};

class FileReader
{
public:
    FileReader();
    FileReader(std::string filePath);
    ~FileReader();

    // Old Methods
    void OpenFile(char* fileName);
    void OpenFile(const char* fileName);
    FileContents* GetFileContents(bool ensureNullTerminated = false);

    // The return of this function is ALWAYS null terminated
    std::string* ReadChars(int count);

    // Function returns NULL when the document is finished
    std::string* NextLine();

    void ResetCursor();

    void Close();

    void DumpFile(std::string outFileName);

private:
    std::fstream* fileStream;

    int GetFileSize();
};

