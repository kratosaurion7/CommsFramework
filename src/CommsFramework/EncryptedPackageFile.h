#pragma once

#include "PackageFile.h"

#include <string>

class EncryptedPackageFile : public PackageFile
{
public:
    EncryptedPackageFile(char* encryptionKey); // Null terminated byte array
    ~EncryptedPackageFile();

protected:
    const char* GetFile(std::string filename, int& fileSize);

    void AddFile(std::string filename, std::string directoryRoot);

    void Save(std::string savePath);

    void Extract(std::string outPath);

    void ReadPackage();


private:
    int EncryptionKeyLength;
    char* EncryptionKey;

    void TransformBuffer(char* buffer, int length);

};