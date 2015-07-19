#include "PackageFile.h"

#include "PointerList.h"

#include "Macros.h"

#include "BitHelper.h"

#include <cstring>

#include <fstream>

PackageFile::PackageFile()
{
	packageHeader = new Header;
	entries = new PointerList<DirectoryEntry*>;

	filesList = new PointerList<std::string>();
}

PackageFile::PackageFile(std::string packageFilePath)
{
	TargetPackage = packageFilePath;
}


PackageFile::~PackageFile()
{
	SAFE_DELETE(packageHeader);
	
	auto it = entries->GetContainer()->begin();

	while (it != entries->GetContainer()->end())
	{
		auto element = *it;

		delete(element);

		it++;
	}

	delete(entries);
}

const char * PackageFile::GetFile(std::string filename, int& fileSize)
{
	std::ifstream packageStream = std::ifstream(TargetPackage);

	char buf[256];
	char* fileContents = NULL;

	packageStream.get(buf, 5); // get(n) method returns at most n-1 elements. Signature is 4


	
	// Step 1. Check it the file is the correct format
	if (strncmp(buf, "PACK", 4) != 0)
		return NULL;

	packageStream.get(buf, sizeof(int));

	//int dirOffset = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
	int dirOffset = BytesToInt(buf);

	bool hasNextFile = true;
	bool fileFound = false;
	packageStream.seekg(dirOffset);

	int filesIndex = 0;
	while (hasNextFile && !fileFound)
	{
		packageStream.get(buf, DIRECTORY_ENTRY_SIZE);
		if (strncmp(filename.c_str(), buf, FILENAME_MAX_LENGTH) == 0)
		{
			int targetFilePos = BytesToInt(&buf[FILENAME_MAX_LENGTH]);
			int targetFileLength = BytesToInt(&buf[FILENAME_MAX_LENGTH + sizeof(int)]);

			int targetFileOffset = HEADER_SIZE + (DIRECTORY_ENTRY_SIZE - 1 * (filesIndex + 1));
			packageStream.seekg(targetFileOffset + targetFilePos);
			fileContents = new char[targetFileLength];
			packageStream.get(fileContents, targetFileLength, NULL);

			fileFound = true;
		}
		
		filesIndex++;
	}

	return fileContents;
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

	int headerSize = 4 + 4 + 4; // Header Size
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


	fileStream.write(packHeader->sig, 4);
	fileStream.write((char*)&packHeader->dirOffset, 4);
	fileStream.write((char*)&packHeader->dirLength, 4);

	auto it2 = entries->GetContainer()->begin();

	int currentDirectoryOffset = 0;

	while (it2 != entries->GetContainer()->end())
	{
		DirectoryEntry* entry = *it2;

		fileStream.write(entry->fileName, sizeof(entry->fileName));
		fileStream.write((char*)&entry->filePosition, sizeof(entry->filePosition));
		fileStream.write((char*)&entry->fileLength, sizeof(entry->fileLength));
		

		it2++;
	}

	auto it3 = entries->GetContainer()->begin();

	while (it3 != entries->GetContainer()->end())
	{
		DirectoryEntry* entry = *it3;

		fileStream.write(entry->fileContents, entry->fileLength);

		it3++;
	}

	fileStream.close();
}
