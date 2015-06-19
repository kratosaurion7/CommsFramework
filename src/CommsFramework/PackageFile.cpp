#include "PackageFile.h"



PackageFile::PackageFile()
{
	fileName = "";
	reader = new FileReader();
}

PackageFile::PackageFile(std::string path)
{
	fileName = path;
	reader = new FileReader();

	reader->OpenFile(path.c_str(), READWRITE);
	auto contents = reader->GetFileContents();
	//data = contents->buffer;
}

PackageFile::~PackageFile()
{
	delete reader;
	delete header;
	for (int i = 0;i < filesCount;i++)
	{
		delete entries[i];
	}

	delete data;
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
