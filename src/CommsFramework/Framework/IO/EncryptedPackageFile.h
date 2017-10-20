#pragma once

#include "PackageFile.h"

#include <stdint.h>
#include <string>

class EncryptedPackageFile : public PackageFile
{
public:
	EncryptedPackageFile(char* encryptionKey, int len);

    EncryptedPackageFile(std::string filename, char* encryptionKey); // Null terminated byte array

    ~EncryptedPackageFile();

protected:

    void ReadBytes(char* targetBuffer, int nbBytes, std::ifstream* stream);

    void WriteBytes(char* sourceBuffer, int nbBytes, std::ofstream* stream);


private:
    size_t EncryptionKeyLength;
    char* EncryptionKey;

    void TransformBuffer(char* buffer, int length);

};