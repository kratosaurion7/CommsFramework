#pragma once

#ifdef WIN32

//#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

#endif

#ifdef _LINUX

// Bad syntax to ensure this part is not compiled
Bla bla bla linux stuff should not compile.

#endif

#include <string>

#include "PointerList.h"

class XFile;

enum DIRECTORY_CREATE_RESULT
{
    DIR_ALREADY_EXIST,
    DIR_PATH_NOT_FOUND
};

class XFile;

#ifdef WIN32
static const wchar_t* currentDotDirName = _T(".");
static const wchar_t* parentDotDirName = _T("..");
#endif

class XDirectory
{
public:
    XDirectory(std::string path);
    ~XDirectory();

    std::string Name;
    std::string FullPath; // The FullPath must NEVER have a trailing slash.

    static XDirectory* OpenDirectory(std::string path);
    PointerList<XFile*>* GetFiles(bool recursive = false);
    PointerList<XDirectory*>* GetDirectories(bool recursive = false);

#ifdef WIN32
    XDirectory(std::wstring path);

    static XDirectory* OpenDirectory(std::wstring path);
#endif


protected:

    bool Check();



#ifdef WIN32
    HANDLE winDirHandle;

    std::wstring DirectoryPath; // Path to the directory, including the \\* characters at the end
#endif

private:
    void FindFilesInDirectory(std::wstring directoryPath, PointerList<XFile*> &filesAggregate, bool recursive = false);
};

XDirectory* GetWorkingDir();

void ChangeWorkingDir(std::string newPath);

#ifdef WIN32
bool IsDotFile(WIN32_FIND_DATA name);
#endif