#include "IOUtilities.h"

#include <assert.h>
#include <string>

#ifdef WIN32

#include <Windows.h>

#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

#include "WindowsHelpers.h"

#endif // WIN32

#include "XFile.h"
#include "XDirectory.h"
#include "StringFunctions.h"

std::string GetLocalFileName(XFile* file)
{
    assert(file != NULL);

    BaseList<std::string>* pathComponents = GetFilePathComponents(file);

    std::string fileName = pathComponents->Last();

    pathComponents->Clear();
    delete(pathComponents);

    return fileName;
}

BaseList<std::string>* GetFilePathComponents(XFile* file)
{
    assert(file != NULL);

    return GetFilePathComponents(file->FilePath);
}

BaseList<std::string>* GetFilePathComponents(std::string path)
{
    BaseList<std::string>* components = StringSplit(path, "\\");

    return components;
}

std::string GetFileExtension(XFile* file)
{
    assert(file != NULL);

    std::string path = file->FilePath;

    int periodIndex = path.find(".");

    std::string fileExt = path.substr(periodIndex, path.length() - periodIndex);

    return fileExt;
}

std::string GetFileName(std::string filePath)
{
    // Get only the file part of the path
    size_t filePartStartIndex = filePath.find_last_of('\\') + 1;
    std::string filePart = filePath.substr(filePartStartIndex, filePath.length() - filePartStartIndex);

    // Get the filename from the filename + extension string
    size_t extIndex = filePart.find_last_of('.');
    std::string fileName = filePart.substr(0, extIndex);

    return fileName;
}

std::string GetParentDirectoryPath(std::string path)
{
    assert(path != "");

    std::string::size_type lastSlash = path.rfind('\\', std::string::npos);

    std::string newString = path.substr(0, lastSlash);

    return newString;
}

std::string GetParentDirectoryPath(XFile * file)
{
    assert(file != NULL);

    return GetParentDirectoryPath(file->FilePath);
}

std::string GetParentDirectoryName(std::string path)
{
    assert(path != "");

    BaseList<std::string>* pathComponents = GetFilePathComponents(path);

    std::string parentDirectoryComponent = pathComponents->Get(pathComponents->Count() - 2); // -2 to skip adjusted from 1-based and to skip the last element (the file itself)

    pathComponents->Clear();
    delete(pathComponents);

    return parentDirectoryComponent;
}

std::string GetParentDirectoryName(XFile* file)
{
    assert(file != NULL);

    return GetParentDirectoryName(file->FilePath);
}

XDirectory* GetParentDirectory(std::string path)
{
    assert(path != "");

    XDirectory* parentDir = new XDirectory(path);

    return parentDir;
}

XDirectory* GetParentDirectory(XFile * file)
{
    assert(file != NULL);

    return GetParentDirectory(file->FilePath);
}

std::string SanitizeFilePath(std::string filePath)
{
    assert(filePath != "");

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
    assert(filePath != "");

    std::string sanitizedFilePath = SanitizeFilePath(filePath);

    return sanitizedFilePath.compare(filePath) == 0;
}

bool IsValidFilePath(std::string filePath)
{
    assert(filePath != "");

    XFile fileTest = XFile(filePath);

    return fileTest.Exists;
}

bool IsValidPath(std::string path)
{
    assert(path != "");

#ifdef WIN32

    std::wstring x = CStringToWideString(path);

    int ret = PathFileExists(x.c_str());

    return ret == 1;

#elif
    return false;

#endif // WIN32
}

void CreatePath(std::string path)
{
    assert(path != "");
    
    BaseList<std::string>* pathComponents = GetFilePathComponents(path);

    int currentComponent = 0;
    std::string pathBuilder;

    while (currentComponent < pathComponents->Count())
    {
        pathBuilder.append(pathComponents->Get(currentComponent));

        if (!IsValidPath(pathBuilder))
        {
#ifdef WIN32
            std::wstring wPath = CStringToWideString(pathBuilder);

            SECURITY_ATTRIBUTES attr;
            // TODO : Check if file, if true don't create
            BOOL ret = CreateDirectory(wPath.c_str(), NULL);

            int i = 0;
            
#endif // WIN32
        }

        currentComponent++;
        pathBuilder.append("\\");

    }

    pathComponents->Clear();
    delete(pathComponents);
}
