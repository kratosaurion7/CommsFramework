#pragma once

#include <string>
#include <stdio.h>

#include <fstream>

enum FileAccessFlags
{
    READ,
    WRITE,
    READWRITE
};

struct FileContents
{
    char* buffer;
    int fileSize;
};

class FileReader
{
public:
    FileReader();
    ~FileReader();

    void OpenFile(char* fileName, FileAccessFlags access);

	void OpenFile(const char* fileName, FileAccessFlags access);

	FileContents* GetFileContents();

	void Close();

private:
	std::fstream* fileStream;
	
	char* newContent;
	int contentSize;

    char* TranslateAccessFlag(FileAccessFlags flag);

	int GetFileSize();
};

