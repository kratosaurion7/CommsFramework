#include "EncryptedPackageFile.h"

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


EncryptedPackageFile::EncryptedPackageFile(char* encryptionKey) : PackageFile()
{
    assert(encryptionKey != NULL);

    this->EncryptionKey = encryptionKey;
    this->EncryptionKeyLength = strlen(encryptionKey);
}

EncryptedPackageFile::~EncryptedPackageFile()
{
    delete(EncryptionKey);
}

//const char* EncryptedPackageFile::GetFile(std::string filename, int& fileSize)
//{
//    assert(filename != "");
//
//    if (!packageRead)
//        this->ReadPackage();
//
//    auto it = this->entries->GetContainer()->begin();
//    while (it != this->entries->GetContainer()->end())
//    {
//        DirectoryEntry* entry = *it;
//
//        if (entry->fileName == filename)
//        {
//            int fileStartPos = entry->filePosition;
//            int size = entry->fileLength;
//
//            char* buf = new char[size];
//
//            std::ifstream reader = std::ifstream(TargetPackage, std::ios::in, std::ios::binary);
//            reader.seekg(fileStartPos);
//            reader.read(buf, size);
//
//            TransformBuffer(buf, size); // Decrypt the file before returning it
//
//            fileSize = size;
//            return buf;
//        }
//    }
//
//    fileSize = 0;
//    return NULL;
//}
//
//void EncryptedPackageFile::Save(std::string savePath)
//{
//}
//
//void EncryptedPackageFile::Extract(std::string outPath)
//{
//}
//
//void EncryptedPackageFile::ReadPackage()
//{
//    std::ifstream fs = std::ifstream(TargetPackage, std::ios::in | std::ios::binary);
//
//    char buf[512];
//    char* fileContents = NULL;
//
//    fs.get(buf, PACK_FILE_SIG_LENGTH + 1); // Reads the signature, the sig is never encrypted
//
//    if (strncmp(buf, "PACK", PACK_FILE_SIG_LENGTH) != 0)
//        return;
//
//    // The rest of the bytes read are all encrypted
//    // Each call to fs.get needs to follow a call to TransformBuffer to decrypt the bytes.
//    fs.get(buf, sizeof(int) + 1);
//    TransformBuffer(buf, sizeof(int) + 1);
//    int dirOffset = BytesToInt(buf);
//
//    fs.get(buf, sizeof(int) + 1);
//    TransformBuffer(buf, sizeof(int) + 1);
//    int directorySize = BytesToInt(buf);
//
//    Header *packHeader = new Header();
//    strncpy(packHeader->sig, "PACK", 4);
//    packHeader->dirOffset = dirOffset;
//    packHeader->dirLength = directorySize;
//
//    if (packageHeader)
//        delete(packageHeader);
//
//    packageHeader = packHeader;
//
//    bool hasNextFile = true;
//    fs.seekg(dirOffset);
//
//    entries->Release();
//
//    int bytesRead = 0;
//    while (hasNextFile)
//    {
//        fs.get(buf, DIRECTORY_ENTRY_SIZE + 1);
//        TransformBuffer(buf, DIRECTORY_ENTRY_SIZE + 1);
//
//        bytesRead += DIRECTORY_ENTRY_SIZE;
//
//        if (bytesRead > directorySize)
//        {
//            hasNextFile = false;
//            break;
//        }
//
//        DirectoryEntry* newEntry = new DirectoryEntry();
//
//        strncpy(newEntry->fileName, buf, strlen(buf));
//
//        int targetFilePos = BytesToInt(&buf[FILENAME_MAX_LENGTH]);
//        int targetFileLength = BytesToInt(&buf[FILENAME_MAX_LENGTH + sizeof(int)]);
//
//        newEntry->fileLength = targetFileLength;
//        newEntry->filePosition = targetFileLength;
//
//        entries->Add(newEntry);
//    }
//
//    packageRead = true;
//}

void EncryptedPackageFile::ReadBytes(char* targetBuffer, int nbBytes, std::ifstream * stream)
{
    stream->get(targetBuffer, nbBytes);

    TransformBuffer(targetBuffer, nbBytes);
}

void EncryptedPackageFile::WriteBytes(char* sourceBuffer, int nbBytes, std::ofstream * stream)
{
    TransformBuffer(sourceBuffer, nbBytes);

    stream->write(sourceBuffer, nbBytes);
}

void EncryptedPackageFile::TransformBuffer(char * buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        char currentByteKey = this->EncryptionKey[length % EncryptionKeyLength];

        buffer[i] ^= currentByteKey;
    }
}
