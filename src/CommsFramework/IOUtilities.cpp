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

std::string GetParentDirectory(XFile* file)
{
    assert(file != NULL);

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

bool IsValidPath(std::string path)
{
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

            BOOL ret = CreateDirectory(wPath.c_str(), NULL);

            int i = 0;
            
#endif // WIN32
        }

        currentComponent++;
        pathBuilder.append("\\");

    }

}
