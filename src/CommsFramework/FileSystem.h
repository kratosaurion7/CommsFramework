#pragma once

#ifdef _WINDOWS

#include "WindowsFile.h"
#include "WindowsDirectory.h"

typedef WindowsFile File;
typedef WindowsDirectory Directory;

//using File = WindowsFile;
//using Directory = WindowsDirectory;

#endif

#ifdef LINUX

#include "LinuxFile"

typedef LinuxFile File; // Or whatever

#endif