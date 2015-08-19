#pragma once

enum FILE_OPEN_MODE
{
    XFILE_READ,
    XFILE_WRITE,
    XFILE_READ_WRITE
};

enum FILE_SHARE_MODE
{
    XSHARE_MODE_NONE,
    XSHARE_READ,
    XSHARE_WRITE
};

enum FILE_OPEN_CREATE_MODE
{
    XCREATE_NEW,
    XCREATE_ALWAYS,
    XOPEN_EXISTING,
    XOPEN_ALWAYS,
    XTRUNCATE_EXISTING
};

#ifdef _WINDOWS

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

#endif

#include <string>

#include "XDirectory.h"

#include "FileReader.h"

class XDirectory;

class XFile
{
public:
    XFile(std::string name); // Automatically opens the file using the Open() function
    ~XFile();

    bool FileValid;
    int FileSize;
    bool Exists;

    std::string FilePath;
    std::string FileName;
    std::string FileExt;
    std::string ParentDirectoryPath;

    // Open with READ mode and SHARE NONE
    bool Open();
    // Opens a file with the given open mode and share mode. If the file does not exist, function goes in error
    bool Open(FILE_OPEN_MODE openMode, FILE_SHARE_MODE shareMode = XSHARE_MODE_NONE);
    // Open a file, if the file does not exist create it with READ WRITE and get a lock on it.
    bool OpenCreate();
    // Opens a file with the given open mode and share mode. If the file does not exist, it is created and opened as READ_WRITE
    bool OpenCreate(FILE_OPEN_CREATE_MODE createMode, FILE_SHARE_MODE shareMode = XSHARE_MODE_NONE);
    void Close();
    bool IsOpen();

    void AppendText(char* text, int size);

    FileContents* Read();
    void Read(char* &buf, int &size);
    void Write(char* buf, int size);

    XDirectory* ParentDirectory();

    // Copy the file to another location
    void CopyTo(std::string filePath, bool overwrite = false);
    // Copy the file to another location, keeping the same file name.
    void CopyTo(XDirectory* targetDir, bool overwrite = false);
    // Move the file to a new location
    void MoveTo(std::string filePath, bool overwrite = false);
    // Move the file to a new directory, keeping the same file name.
    void MoveTo(XDirectory* targetDir, bool overwrite = false);

    void Delete();
protected:

    int TranslateFileOpenMode(FILE_OPEN_MODE mode);
    int TranslateFileShareMode(FILE_SHARE_MODE mode);
    int TranslateOpenCreateMode(FILE_OPEN_CREATE_MODE mode);

    void CreateAndAssignPathInfo();

    XDirectory* parentDir;
    std::string CleanupDirectoryName(std::string stringToClean);

    bool Check();

    __int64 GetSize();

    void AssignFileSize();

#ifdef _WINDOWS
    HANDLE winFileHandle;

#endif
};

std::string GetFileNameFromFilePath(std::string filePath);