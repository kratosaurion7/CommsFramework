#pragma once

#include "PackageFile.h"

#include <string>

class EncryptedPackageFile : public PackageFile
{
public:
    EncryptedPackageFile(std::string filename, char* encryptionKey); // Null terminated byte array
    ~EncryptedPackageFile();

    //const char* GetFile(std::string filename, int& fileSize);

    //void Save(std::string savePath);

    //void Extract(std::string outPath);


protected:

    //void ReadPackage();

    void ReadBytes(char* targetBuffer, int nbBytes, std::ifstream* stream);

    void WriteBytes(char* sourceBuffer, int nbBytes, std::ofstream* stream);


private:
    int EncryptionKeyLength;
    char* EncryptionKey;

    void TransformBuffer(char* buffer, int length);

};