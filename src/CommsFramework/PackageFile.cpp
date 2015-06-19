#include "PackageFile.h"



PackageFile::PackageFile()
{
	fileName = "";
}

PackageFile::PackageFile(std::string path)
{
	fileName = path;
}


PackageFile::~PackageFile()
{
}

char * PackageFile::GetFile(std::string fileName, int & size)
{
	return 0;
}

DirectoryEntry * PackageFile::GetFilesList(int & size)
{
	return NULL;
}

void PackageFile::AddFile(std::string fileName, char * data, int size)
{
}

void PackageFile::SortPackage(SortingMethods sortingMethod)
{
}

void PackageFile::Save(std::string path)
{
}
