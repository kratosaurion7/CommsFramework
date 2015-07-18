#pragma once

#include <cstdio>

#include <string>

#include "FileReader.h"

#include "PointerList.h"

struct Header {
	char sig[5];
	int dirOffset;
	int dirLength;
};

struct DirectoryEntry {
	char fileName[256];
	int filePosition;
	int fileLength;

	char* fileContents;
};

class PackageFile
{
public:
	PackageFile();
	
	~PackageFile();

	void AddFile(std::string filename);

	void RemoveFile(std::string filename);

	void Save(std::string savePath);
	
private:
	Header* packageHeader;

	PointerList<std::string>* filesList;

	PointerList<DirectoryEntry*>* entries;

	std::string OutputFileName;

};

