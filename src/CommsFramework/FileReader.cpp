#include "FileReader.h"

#include <stdio.h>

#include <string>

#define READ_BLOCK_SIZE 128

FileReader::FileReader()
{
	fileStream = new std::fstream();
	newContent = NULL;
}

FileReader::~FileReader()
{
	if (fileStream != NULL)
		fileStream->close();

	//delete(newContent); Throws exception sometimes
	delete(fileStream);
}

void FileReader::OpenFile(char* fileName)
{
	fileStream->open(fileName, std::ios::in | std::ios::binary);
}

void FileReader::OpenFile(const char* fileName)
{
	fileStream->open(fileName, std::ios::in | std::ios::binary);
}

FileContents* FileReader::GetFileContents(bool ensureNullTerminated)
{
    if (fileStream == NULL || !fileStream->good())
        return NULL;
	
	int fileSize = GetFileSize();

	newContent = new char[fileSize + 1];

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

void FileReader::Close()
{
	if (fileStream != NULL)
		fileStream->close();
}
void FileReader::DumpFile(std::string outFileName)
{
	fileStream->seekg(0, 0);

	std::ofstream outStream = std::ofstream(outFileName.c_str(), std::ofstream::out | std::ofstream::binary);

	int fileSize = GetFileSize();

	char* contents = new char[fileSize];

	fileStream->read(contents, fileSize);

	outStream.write(contents, fileSize);

	delete(contents);

	outStream.close();

	fileStream->seekg(0, 0);
}

int FileReader::GetFileSize()
{
	int fileSize = 0;

	if (fileStream->good())
	{
		int currentPos = fileStream->tellg();

		fileStream->seekg(0, std::ios::end);

		fileSize = fileStream->tellg();

		fileStream->seekg(150);


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
