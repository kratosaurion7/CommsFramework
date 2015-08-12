#pragma once

#ifdef _WINDOWS

#define File WindowsFile
#define Directory WindowsDirectory

#include "WindowsFile.h"
#include "WindowsDirectory.h"


//using File = WindowsFile;
//using Directory = WindowsDirectory;

#endif

#ifdef LINUX

#include "LinuxFile"

typedef LinuxFile File; // Or whatever

#endif