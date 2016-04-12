#include "IOUtilities.h"

#include "XFile.h"

std::string GetLocalFileName(XFile* file)
{
    return std::string();
}

BaseList<std::string>* GetFilePathComponents(XFile* file)
{
    return nullptr;
}

std::string GetFileExtension(XFile* file)
{
    return std::string();
}

std::string GetParentDirectory(XFile* file)
{
    std::string path = file->FilePath;

    // Find last '\' character
    int lastIndex = 0;

    for (int i = 0; i < path.length(); i++)
    {
        char currentChar = path.at(i);

        if (currentChar == 92)
            lastIndex = currentChar;
    }

    return std::string();
}

std::string SanitizeFilePath(std::string filePath)
{
    return std::string();
}

bool IsSanitizedFilePath(std::string filePath)
{
    return false;
}

bool IsValidFilePath(std::string filePath)
{
    return false;
}
