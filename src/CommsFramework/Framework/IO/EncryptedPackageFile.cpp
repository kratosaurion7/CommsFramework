#include "EncryptedPackageFile.h"

#include <cstring>
#include <fstream>
#include <assert.h>

#include "Filesystem/XFile.h"
#include "Filesystem/XDirectory.h"
#include "Collections/PointerList.h"
#include "Macros.h"
#include "System/BitHelper.h"
#include "System/Utilities.h"
#include "Filesystem/IOUtilities.h"
#include "Utilities/StringFunctions.h"


EncryptedPackageFile::EncryptedPackageFile(char* encryptionKey, int len) : PackageFile()
{
	assert(encryptionKey != NULL);
	assert(len != 0);
	

	this->EncryptionKey = encryptionKey;
	this->EncryptionKeyLength = len;
}

EncryptedPackageFile::EncryptedPackageFile(std::string filename, char* encryptionKey) : PackageFile(filename)
{
    assert(filename != "");
    assert(encryptionKey != NULL);

    this->EncryptionKey = encryptionKey;
    this->EncryptionKeyLength = strlen(encryptionKey);
}

EncryptedPackageFile::~EncryptedPackageFile()
{
    delete(EncryptionKey);
}

void EncryptedPackageFile::ReadBytes(char* targetBuffer, int nbBytes, std::ifstream* stream)
{
    stream->read(targetBuffer, nbBytes);

    TransformBuffer(targetBuffer, nbBytes);
}

void EncryptedPackageFile::WriteBytes(char* sourceBuffer, int nbBytes, std::ofstream* stream)
{
    TransformBuffer(sourceBuffer, nbBytes);

    stream->write(sourceBuffer, nbBytes);
}

void EncryptedPackageFile::TransformBuffer(char* buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        char currentByteKey = this->EncryptionKey[i % EncryptionKeyLength];

        buffer[i] ^= currentByteKey;
    }
}