#pragma once

#define WIN32_LEAN_AND_MEAN

#include "PointerList.h"

#include <string>

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

#include "WindowsFile.h"

#include "FileSystem.h"

class WindowsDirectory;
class WindowsFile;

enum DIRECTORY_CREATE_RESULT
{
    DIR_ALREADY_EXIST,
    DIR_PATH_NOT_FOUND
};

Directory* GetWorkingDir();

void ChangeWorkingDir(std::string newPath);

class WindowsDirectory
{
public:
    WindowsDirectory();
    ~WindowsDirectory();

    static Directory* OpenDirectory(std::string path);

    std::string Name();

    std::string FullPath();

    PointerList<File*>* GetFiles(bool recursive = false);

    PointerList<Directory*>* GetDirectories(bool recursive = false);
};

