#include "PackageFile.h"

#include "PointerList.h"

#include "Macros.h"

#include <cstring>

#include <fstream>

PackageFile::PackageFile()
{
	packageHeader = new Header;
	entries = new PointerList<DirectoryEntry*>;

	filesList = new PointerList<std::string>();
}


PackageFile::~PackageFile()
{
	SAFE_DELETE(packageHeader);
	
	auto it = entries->GetContainer()->begin();

	// TODO : Create a clear method in the BaseList
	while (it != entries->GetContainer()->end())
	{
		auto element = *it;

		delete(element);

		it++;
	}

	delete(entries);
}

void PackageFile::AddFile(std::string filename)
{
	filesList->Add(filename);
}

void PackageFile::RemoveFile(std::string filename)
{
	filesList->RemoveObject(filename);
}

void PackageFile::Save(std::string savePath)
{
	OutputFileName = savePath;

	FileReader* rdr = new FileReader();

	int headerSize = 5 + 4 + 4; // Header Size
	int directorySize = 0; // Directory size
	int bufPos = 0; // Data section size
	

	auto it = filesList->GetContainer()->begin();

	while (it != filesList->GetContainer()->end())
	{
		std::string fileName = *it;

		rdr->OpenFile(fileName.c_str(), FileAccessFlags::READ);
		
		FileContents* contents = rdr->GetFileContents();

		DirectoryEntry* newFileEntry = new DirectoryEntry();

		strcpy(newFileEntry->fileName, const_cast<char*>(fileName.c_str()));
		newFileEntry->fileLength = contents->fileSize;
		newFileEntry->filePosition = bufPos;
		newFileEntry->fileContents = contents->buffer;

		bufPos += contents->fileSize;

		directorySize += sizeof(newFileEntry->fileName) + sizeof(newFileEntry->fileLength) + sizeof(newFileEntry->filePosition);

		entries->Add(newFileEntry);

		rdr->Close();

		it++;
	}

	int fileSize = headerSize + bufPos + directorySize;
	char* fileBuffer = new char[fileSize];

	std::ofstream fileStream;
	fileStream.open(OutputFileName.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

	auto x = sizeof(char[256]);

	Header *packHeader = new Header();
	strcpy(packHeader->sig, "PACK");
	packHeader->dirOffset = headerSize;
	packHeader->dirLength = directorySize;


	fileStream.write(packHeader->sig, 5);
	fileStream.write((char*)&packHeader->dirOffset, 4);
	fileStream.write((char*)&packHeader->dirLength, 4);

	auto it2 = entries->GetContainer()->begin();

	int currentDirectoryOffset = 0;

	while (it2 != entries->GetContainer()->end())
	{
		DirectoryEntry* entry = *it2;

		fileStream.write(entry->fileName, sizeof(entry->fileName));
		fileStream.write((char*)&entry->fileLength, sizeof(entry->fileLength));
		fileStream.write((char*)&entry->filePosition, sizeof(entry->filePosition));

		it2++;
	}

	auto it3 = entries->GetContainer()->begin();

	while (it3 != entries->GetContainer()->end())
	{
		DirectoryEntry* entry = *it3;

		fileStream.write(entry->fileContents, entry->fileLength);

		it3++;
	}

	//FILE* outFile = fopen(OutputFileName.c_str(), "w+");

	//fwrite(fileBuffer, sizeof(char), fileSize, outFile);

	//fclose(outFile);

	fileStream.close();
}
