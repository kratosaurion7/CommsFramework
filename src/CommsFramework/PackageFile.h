#pragma once

#include <cstdio>

#include <string>

#include "FileReader.h"

#include "PointerList.h"

#define FILENAME_MAX_LENGTH 32
#define PACK_FILE_SIG_LENGTH 4

/*
	=Format=
	Header
	(4 bytes) signature = 'PACK'
	(4 bytes, int) directory offeset
	(4 bytes, int) directory lenght

	Directory
	(56 bytes, char) file name
	(4 bytes, int) file position
	(4 bytes, int) file lenght

	File at each position (? bytes, char) file data
*/

#define HEADER_SIZE 12
struct Header {
	char sig[PACK_FILE_SIG_LENGTH];
	int dirOffset;
	int dirLength;
};

#define DIRECTORY_ENTRY_SIZE 40
struct DirectoryEntry {
	char fileName[FILENAME_MAX_LENGTH];
	int filePosition;
	int fileLength;

	char* fileContents;
};

class PackageFile
{
public:
	PackageFile();

	PackageFile(std::string packageFilePath);
	
	~PackageFile();

	const char* GetFile(std::string filename, int& fileSize);

	void AddFile(std::string filename);

	void RemoveFile(std::string filename);

	void Save(std::string savePath);
	
private:
	Header* packageHeader;

	BaseList<std::string>* filesList;

	PointerList<DirectoryEntry*>* entries;

	FileContents* contents;

	std::string TargetPackage;

	std::string OutputFileName;
};

