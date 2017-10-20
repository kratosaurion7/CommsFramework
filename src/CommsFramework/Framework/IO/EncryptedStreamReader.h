#pragma once

#include <string>

class EncryptedStreamReader
{
private:
    char* EncryptionKey;
    int KeyLength;

public:
    EncryptedStreamReader(char* key, int keyLen);
    ~EncryptedStreamReader();

    char* ReadFile(std::string fileName, int& outDataLength);

    void WriteFile(std::string fileName, char* data, int dataLength);
};