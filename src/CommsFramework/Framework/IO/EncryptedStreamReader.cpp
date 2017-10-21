#include "EncryptedStreamReader.h"

#include "IO/FileReader.h"
#include "Filesystem/XFile.h"

EncryptedStreamReader::EncryptedStreamReader(char* key, int keyLen)
{
    this->EncryptionKey = key;
    this->KeyLength = keyLen;
}


EncryptedStreamReader::~EncryptedStreamReader()
{
    delete(this->EncryptionKey);
}

char* EncryptedStreamReader::ReadFile(std::string fileName, int& outDataLength)
{
    char* outputBuffer;
    FileReader r = FileReader(fileName);
    FileContents* contents = r.GetFileContents();
    
    outputBuffer = new char[contents->fileSize];

    for (int i = 0; i < contents->fileSize; i++)
    {
        outputBuffer[i] = contents->buffer[i % KeyLength] ^ EncryptionKey[i % KeyLength];
    }

    outDataLength = contents->fileSize;

    delete(contents);
    r.Close();

    return outputBuffer;
}

void EncryptedStreamReader::WriteFile(std::string fileName, char* data, int dataLength)
{
    char* encryptedBuffer = new char[dataLength];

    for (int i = 0; i < dataLength; i++)
    {
        encryptedBuffer[i] = data[i % KeyLength] ^ EncryptionKey[i % KeyLength];
    }

    XFile writer = XFile(fileName);
    writer.OpenCreate();
    writer.Write(encryptedBuffer, dataLength);

    writer.Close();
    delete(encryptedBuffer);
}
