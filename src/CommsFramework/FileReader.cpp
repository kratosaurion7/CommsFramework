#include "FileReader.h"

#include <stdio.h>

#include <string>



#define READ_BLOCK_SIZE 128

FileReader::FileReader()
{
	fileStream = new std::fstream();
	newContent = NULL;
};

FileReader::~FileReader()
{
	if (fileStream != NULL)
		fileStream->close();

	delete(newContent);
	delete(fileStream);
};

void FileReader::OpenFile(char* fileName)
{
	OpenFile(fileName);
};

void FileReader::OpenFile(const char* fileName)
{
	fileStream->open(fileName, std::ios::in | std::ios::binary);


};

FileContents* FileReader::GetFileContents()
{
    char buf[READ_BLOCK_SIZE];

    if (fileStream == NULL || !fileStream->good())
        return NULL;

	int fileSize = GetFileSize();
	int bufIndex = 0;

	newContent = new char[fileSize];
	newContent[0] = '\0';

    while (!fileStream->eof() && bufIndex < fileSize)
    {
		int readBlockSize = READ_BLOCK_SIZE;
		
		int remainingBytes = fileSize - bufIndex;

		fileStream->get(buf, readBlockSize, NULL);

		strcat(newContent, buf);

		bufIndex += readBlockSize;
    }

    FileContents *fileContents = new FileContents();
	fileContents->buffer = newContent;
	fileContents->fileSize = fileSize;

    return fileContents;
};

void FileReader::Close()
{
	if (fileStream != NULL)
		fileStream->close();
};

int FileReader::GetFileSize()
{
	int fileSize = 0;

	if (fileStream->good())
	{
		int currentPos = fileStream->tellg();

		fileStream->seekg(0, std::ios::end);

		fileSize = fileStream->tellg();

		fileStream->seekg(0, currentPos);
	}

	return fileSize;
};