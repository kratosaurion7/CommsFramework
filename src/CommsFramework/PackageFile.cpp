#include "PackageFile.h"

#include <cstring>
#include <fstream>
#include <assert.h>

#include "XFile.h"
#include "XDirectory.h"
#include "PointerList.h"
#include "Macros.h"
#include "BitHelper.h"
#include "Utilities.h"
#include "IOUtilities.h"
#include "StringFunctions.h"
#include "EncryptedPackageFile.h"


PackageFile::PackageFile()
{
    packageHeader = new Header;
    contents = NULL;
    entries = new PointerList<DirectoryEntry*>;

    filesList = new PointerList<FileListEntry*>();
    packageRead = false;
}

PackageFile::PackageFile(std::string packageFilePath)
{
    packageHeader = new Header;
    contents = NULL;
    entries = new PointerList<DirectoryEntry*>;

    filesList = new PointerList<FileListEntry*>();

    TargetPackage = packageFilePath;
    packageRead = false;
}


PackageFile::~PackageFile()
{
    delete(packageHeader);

    delete(contents);

    filesList->Clear();
    delete(filesList);

    // Since DirectoryEntry are structures, need to do the constructor myself.
    auto it = this->entries->GetContainer()->begin();
    while (it != this->entries->GetContainer()->end())
    {
        DirectoryEntry* entry = *it;
        delete(entry->fileContents);
        delete(entry);

        it++;
    }

    entries->Clear();
    delete(entries);
}

const char* PackageFile::GetFile(std::string filename, int& fileSize)
{
    std::ifstream packageStream = std::ifstream(TargetPackage, std::ios::in | std::ios::binary);

    char buf[512];
    char* fileContents = NULL;

    packageStream.read(buf, PACK_FILE_SIG_LENGTH);
    //packageStream.get(buf, PACK_FILE_SIG_LENGTH + 1); // get(n) method returns at most n-1 elements. Signature is 4

    // Step 1. Check it the file is the correct format
    if (strncmp(buf, "PACK", PACK_FILE_SIG_LENGTH) != 0)
        return NULL;

    ReadBytes(buf, sizeof(int), &packageStream);
    //packageStream.get(buf, sizeof(int));

    int dirOffset = BytesToInt(buf);

    bool hasNextFile = true;
    bool fileFound = false;
    packageStream.seekg(dirOffset);

    int filesIndex = 0;
    while (hasNextFile && !fileFound)
    {
        ReadBytes(buf, DIRECTORY_ENTRY_SIZE, &packageStream);
        //packageStream.read(buf, DIRECTORY_ENTRY_SIZE);
        if (strncmp(filename.c_str(), buf, FILENAME_MAX_LENGTH) == 0)
        {
            int targetFilePos = BytesToInt(&buf[FILENAME_MAX_LENGTH]);
            int targetFileLength = BytesToInt(&buf[FILENAME_MAX_LENGTH + sizeof(int)]);

            packageStream.seekg(targetFilePos);
            fileContents = new char[targetFileLength];
            ReadBytes(fileContents, targetFileLength, &packageStream);
            //packageStream.read(fileContents, targetFileLength);

            fileSize = targetFileLength;
            fileFound = true;
        }

        if (strcmp(buf, "") == 0)
        {
            hasNextFile = false;
        }

        filesIndex++;
    }

    return fileContents;
}

PointerList<std::string>* PackageFile::GetAllFiles()
{
    PointerList<std::string>* ret = new PointerList<std::string>();

    this->ReadPackage();

    auto it = entries->GetContainer()->begin();
    while (it != entries->GetContainer()->end())
    {
        DirectoryEntry* entry = (*it);

        ret->Add(entry->fileName);

        it++;
    }

    return ret;
}

void PackageFile::AddFile(std::string filename)
{
    this->AddFile(filename, "");
}

void PackageFile::AddFile(XFile* file)
{
    this->AddFile(file->FilePath, "");
}

void PackageFile::AddFile(std::string filename, std::string directoryRoot)
{
    FileListEntry* newFile = new FileListEntry();
    newFile->File = new XFile(filename);
    newFile->File->Close();
    
    if (directoryRoot == "")
    {
        newFile->RelativeDirectoryParentRoot = "";
    }
    else
    {
        newFile->RelativeDirectoryParentRoot = GetParentDirectoryPath(directoryRoot);
        newFile->RelativeDirectoryParentRoot.append("\\"); // TODO : HAcked for now, decide if want trailing slashes
    }

    filesList->Add(newFile);
}

void PackageFile::AddDirectory(std::string directoryPath)
{
    XDirectory dir = XDirectory(directoryPath);

    this->AddDirectory(&dir);
}

void PackageFile::AddDirectory(XDirectory* directory)
{
    PointerList<XFile*>* files = directory->GetFiles(true);

    auto it = files->GetContainer()->begin();
    while (it != files->GetContainer()->end())
    {
        XFile* file = *it;

        this->AddFile(file->FilePath, directory->FullPath);

        it++;
    }

    files->Release();
    delete(files);
}

void PackageFile::RemoveFile(std::string filename)
{
    //filesList->RemoveObject(filename);
}

EncryptedPackageFile* PackageFile::SaveEncrypt(std::string savePath, char* key)
{
    assert(savePath != "");
    assert(key != NULL);

    EncryptedPackageFile* newPackage = new EncryptedPackageFile(key, strlen(key));

    newPackage->entries->AddRange(this->entries);
    newPackage->filesList->AddRange(this->filesList);

    newPackage->Save(savePath);

    return newPackage;
}

void PackageFile::Save(std::string savePath)
{
    OutputFileName = savePath;

    FileReader rdr;

    int headerSize = HEADER_SIZE; // Header Size
    int directorySize = 0; // Directory size
    int bufPos = 0; // Data section size

    auto it = filesList->GetContainer()->begin();

    while (it != filesList->GetContainer()->end())
    {
        FileListEntry* fileListing = *it;

        std::string fileName;

        if (fileListing->RelativeDirectoryParentRoot == "")
        {
            fileName = fileListing->File->FileName;
        }
        else
        {
            fileName = StringSubtract(fileListing->File->FilePath, fileListing->RelativeDirectoryParentRoot);
        }        

        rdr.OpenFile(fileListing->File->FilePath.c_str());

        if (contents != NULL)
            delete(contents);

        contents = rdr.GetFileContents();

        DirectoryEntry* newFileEntry = new DirectoryEntry();

        strcpy(newFileEntry->fileName, const_cast<char*>(fileName.c_str()));
        newFileEntry->fileLength = contents->fileSize;
        newFileEntry->filePosition = bufPos;

        newFileEntry->fileContents = new char[contents->fileSize];
        memcpy(newFileEntry->fileContents, contents->buffer, contents->fileSize);

        bufPos += contents->fileSize;

        directorySize += sizeof(newFileEntry->fileName) + sizeof(newFileEntry->fileLength) + sizeof(newFileEntry->filePosition);

        entries->Add(newFileEntry);

        rdr.Close();

        it++;
    }

    int fileSize = headerSize + bufPos + directorySize;

    std::ofstream fileStream;
    fileStream.open(OutputFileName.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

    Header *packHeader = new Header();
    strncpy(packHeader->sig, "PACK", 4);
    packHeader->dirOffset = headerSize;
    packHeader->dirLength = directorySize;


    //fileStream.write(packHeader->sig, 4);
    //fileStream.write((char*)&packHeader->dirOffset, 4);
    //fileStream.write((char*)&packHeader->dirLength, 4);

    fileStream.write(packHeader->sig, 4); // Don't encrypt the package signature.
    WriteBytes((char*)&packHeader->dirOffset, 4, &fileStream);
    WriteBytes((char*)&packHeader->dirLength, 4, &fileStream);

    delete(packHeader);

    auto it2 = entries->GetContainer()->begin();

    int currentDirectoryOffset = 0;
    int currentDataSize = 0;

    while (it2 != entries->GetContainer()->end())
    {
        DirectoryEntry* entry = *it2;

        WriteBytes(entry->fileName, sizeof(entry->fileName), &fileStream);
        //fileStream.write(entry->fileName, sizeof(entry->fileName));
        int currPos = headerSize + directorySize + currentDataSize;

		char* filePosCopy = new char[4];
		memcpy(filePosCopy, (char*)&entry->filePosition, 4);
        WriteBytes(filePosCopy, sizeof(filePosCopy), &fileStream);
        //fileStream.write((char*)&currPos, sizeof(entry->filePosition));

        char* fileLengthCopy = new char[4];
        memcpy(fileLengthCopy, (char*)&entry->fileLength, 4);
        WriteBytes(fileLengthCopy, sizeof(fileLengthCopy), &fileStream);
        //fileStream.write((char*)&entry->fileLength, sizeof(entry->fileLength));

        currentDataSize += entry->fileLength;
        it2++;
    }

    auto it3 = entries->GetContainer()->begin();

    while (it3 != entries->GetContainer()->end())
    {
        DirectoryEntry* entry = *it3;

        WriteBytes(entry->fileContents, entry->fileLength, &fileStream);
        //fileStream.write(entry->fileContents, entry->fileLength);

        it3++;
    }

    fileStream.close();
}

void PackageFile::Extract(std::string outPath)
{
    if (!packageRead)
    {
        this->ReadPackage();
    }

    // Loop the directory entries
    auto it = this->entries->GetContainer()->begin();
    while (it != this->entries->GetContainer()->end())
    {
        DirectoryEntry* entry = *it;

        std::string finalFilePath;
        if (outPath != "")
        {
            finalFilePath.append(outPath);
            finalFilePath.append("\\");
        }
        
        finalFilePath.append(entry->fileName);

        XFile newFile = XFile(finalFilePath);
        
        // Need to ensure the file path (folders are contained in the file entry name)
        // coming from the package is created.
        
        std::string parentDir = GetParentDirectoryPath(finalFilePath);
        
        // This is used to skip creating the directory when going over a file without directories.
        if(parentDir != finalFilePath)
            CreatePath(parentDir);

        int bufSize = 0;
        char* buf = (char*)this->GetFile(entry->fileName, bufSize);

        assert(bufSize == entry->fileLength);

        newFile.OpenCreate();
        newFile.Write(buf, entry->fileLength);
        newFile.Close();

        it++;
    }

}


void PackageFile::ReadPackage()
{
    std::ifstream packageStream = std::ifstream(TargetPackage, std::ios::in | std::ios::binary);

    char buf[512];
    char* fileContents = NULL;

	packageStream.read(buf, PACK_FILE_SIG_LENGTH);
    //ReadBytes(buf, PACK_FILE_SIG_LENGTH, &packageStream);
    //packageStream.get(buf, PACK_FILE_SIG_LENGTH + 1);	// get(n) method returns at most n-1 elements. Signature is 4

    if (strncmp(buf, "PACK", PACK_FILE_SIG_LENGTH) != 0)
        return;

    ReadBytes(buf, sizeof(int), &packageStream);
    //packageStream.get(buf, sizeof(int) + 1);
    int dirOffset = BytesToInt(buf);

    ReadBytes(buf, sizeof(int), &packageStream);
    //packageStream.get(buf, sizeof(int) + 1);
    int directorySize = BytesToInt(buf);

    Header *packHeader = new Header();
    strncpy(packHeader->sig, "PACK", 4);
    packHeader->dirOffset = dirOffset;
    packHeader->dirLength = directorySize;

    if (packageHeader)
        delete(packageHeader);

    packageHeader = packHeader;

    bool hasNextFile = true;
    packageStream.seekg(dirOffset);

    entries->Release();

    int bytesRead = 0;
    while (hasNextFile)
    {
        ReadBytes(buf, DIRECTORY_ENTRY_SIZE, &packageStream);
        bytesRead += DIRECTORY_ENTRY_SIZE;

        if (bytesRead > directorySize)
        {
            hasNextFile = false;
            break;
        }

        DirectoryEntry* newEntry = new DirectoryEntry();

        strncpy(newEntry->fileName, buf, strlen(buf));

        int targetFilePos = BytesToInt(&buf[FILENAME_MAX_LENGTH]);
        int targetFileLength = BytesToInt(&buf[FILENAME_MAX_LENGTH + sizeof(int)]);

        newEntry->filePosition = targetFilePos;
        newEntry->fileLength = targetFileLength;

        entries->Add(newEntry);
    }

    packageRead = true;
}

void PackageFile::ReadBytes(char* targetBuffer, int nbBytes, std::ifstream* stream)
{
    stream->read(targetBuffer, nbBytes);
}

void PackageFile::WriteBytes(char* targetBuffer, int nbBytes, std::ofstream* stream)
{
    stream->write(targetBuffer, nbBytes);
}
