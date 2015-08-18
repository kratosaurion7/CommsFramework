#pragma once

#ifdef _WINDOWS

#define WIN32_LEAN_AND_MEAN

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

#include "PointerList.h"
#include <string>
#include "XFile.h"
#include "XDirectory.h"

enum DIRECTORY_CREATE_RESULT
{
    DIR_ALREADY_EXIST,
    DIR_PATH_NOT_FOUND
};

class XFile;

#ifdef _WINDOWS
static const wchar_t* currentDotDirName = _T(".");
static const wchar_t* parentDotDirName = _T("..");
#endif

class XDirectory
{
public:
    XDirectory();
	XDirectory(std::string path);
    ~XDirectory();

	std::string Name;
	std::string FullPath; // The FullPath must NEVER have a trailing slash.

    static XDirectory* OpenDirectory(std::string path);
    PointerList<XFile*>* GetFiles(bool recursive = false);
    PointerList<XDirectory*>* GetDirectories(bool recursive = false);

#ifdef _WINDOWS
	XDirectory(std::wstring path);

	static XDirectory* OpenDirectory(std::wstring path);
#endif


protected:

	bool Check();

#ifdef _WINDOWS
	HANDLE winDirHandle;

	TCHAR dirPath[MAX_PATH]; // Path to the directory
#endif

private:
    void FindFilesInDirectory(wchar_t* directoryPath, PointerList<XFile*> &filesAggregate, bool recursive = false);
};

XDirectory* GetWorkingDir();

void ChangeWorkingDir(std::string newPath);

#ifdef _WINDOWS
bool IsDotFile(WIN32_FIND_DATA name);
#endif