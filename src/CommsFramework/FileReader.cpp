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

void FileReader::OpenFile(char* fileName, FileAccessFlags access)
{
	OpenFile(fileName, access);
};

void FileReader::OpenFile(const char* fileName, FileAccessFlags access)
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

		if (fileSize - remainingBytes < readBlockSize)
		{
			readBlockSize = remainingBytes + 1;
			// Adding +1 to the read because fgets seems to place a null char at the last index of the returned string
		}

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