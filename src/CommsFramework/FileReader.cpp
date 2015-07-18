#include "FileReader.h"

#include <stdio.h>

#include <string>

#define READ_BLOCK_SIZE 128

FileReader::FileReader()
{
    file = NULL;
};

FileReader::~FileReader()
{
    if (file != NULL)
        fclose(file);

	delete(newContent);
};

void FileReader::OpenFile(char* fileName, FileAccessFlags access)
{
	OpenFile(fileName, access);
};

void FileReader::OpenFile(const char* fileName, FileAccessFlags access)
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

	int fileSize = GetFileSize(file);
	int bufIndex = 0;

	newContent = new char[fileSize];
	newContent[0] = '\0';

    while (!feof(file) && bufIndex < fileSize)
    {
		int readBlockSize = READ_BLOCK_SIZE;
		
		int remainingBytes = fileSize - bufIndex;

		if (fileSize - remainingBytes < readBlockSize)
		{
			readBlockSize = remainingBytes + 1;
			// Adding +1 to the read because fgets seems to place a null char at the last index of the returned string
		}

        if (fgets(buf, readBlockSize, file) == NULL)
            break;

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
	if (file != NULL)
		fclose(file);
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

int FileReader::GetFileSize(FILE* target)
{
	if (target != NULL)
	{
		fseek(target, 0, SEEK_END);
		int size = ftell(target);

		fseek(target, 0, 0);

		return size;
	}

	return 0;
};