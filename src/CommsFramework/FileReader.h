#pragma once

#include <string>
#include <stdio.h>

#include <fstream>

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

    void OpenFile(char* fileName);

	void OpenFile(const char* fileName);

	FileContents* GetFileContents(bool ensureNullTerminated = false);

	void Close();

	void DumpFile(std::string outFileName);

private:
	std::fstream* fileStream;
	
	char* newContent;
	int contentSize;

	int GetFileSize();
};

