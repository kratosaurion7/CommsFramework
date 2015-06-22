#pragma once

#include <cstdio>

#include <string>

#include "FileReader.h"

enum SortingMethods {

};

struct Header {
	char* sig = "PACK";
	int dirOffset;
	int dirLength;
};

struct DirectoryEntry {
	char* fileName[56];
	int filePosition;
	int fileLength;
};

class PackageFile
{
public:
	PackageFile();
	
	PackageFile(std::string path);

	~PackageFile();

	char* GetFile(std::string fileName, int &size);

	DirectoryEntry* GetFilesList(int &size);

	void AddFile(std::string fileName, char* data, int size);

	void SortPackage(SortingMethods sortingMethod);

	void BuildFromDirectory(std::string dir);

	void OpenPackage(std::string path);

	void Save(std::string path);
private:

	std::string fileName;

	Header* header;
	DirectoryEntry** entries;
	int filesCount;
	char* data;

	void BuildStructures();
	
	// File stuff
	FileReader* reader;
};

