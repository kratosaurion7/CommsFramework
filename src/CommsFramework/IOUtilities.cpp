#include "IOUtilities.h"

#include <string>

#include "XFile.h"
#include "StringFunctions.h"

std::string GetLocalFileName(XFile* file)
{
    BaseList<std::string>* pathComponents = GetFilePathComponents(file);

    std::string fileName = pathComponents->Last();

    pathComponents->Clear();
    delete(pathComponents);

    return fileName;
}

BaseList<std::string>* GetFilePathComponents(XFile* file)
{
    BaseList<std::string>* components = StringSplit(file->FilePath, "\\");

    return components;
}

std::string GetFileExtension(XFile* file)
{
    std::string path = file->FilePath;

    int periodIndex = path.find(".");

    std::string fileExt = path.substr(periodIndex, path.length() - periodIndex);

    return fileExt;
}

std::string GetParentDirectory(XFile* file)
{
    BaseList<std::string>* pathComponents = GetFilePathComponents(file);

    std::string parentDirectoryComponent = pathComponents->Get(pathComponents->Count() - 1);

    pathComponents->Clear();
    delete(pathComponents);

    return parentDirectoryComponent;
}

std::string SanitizeFilePath(std::string filePath)
{
    // Replace the front slashes by backslashes

    int x = 0;

    x = filePath.find("/", 0);
    while (x != std::string::npos)
    {
        std::string newStringMaybe = filePath.replace(x, 1, "\\");
    }

    return filePath;
}

bool IsSanitizedFilePath(std::string filePath)
{
    std::string sanitizedFilePath = SanitizeFilePath(filePath);

    return sanitizedFilePath.compare(filePath) == 0;
}

bool IsValidFilePath(std::string filePath)
{
    XFile fileTest = XFile(filePath);

    return fileTest.Exists;
}
