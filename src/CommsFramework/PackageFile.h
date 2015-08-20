#pragma once

#include <cstdio>

#include <string>

#include "FileReader.h"

#include "PointerList.h"

#define FILENAME_MAX_LENGTH 32
#define PACK_FILE_SIG_LENGTH 4

/*
    =Format=
    Header
    (4 bytes) signature = 'PACK'
    (4 bytes, int) offset to start of directory (offset is absolute)
    (4 bytes, int) directory lenght

    Directory entries
    (32 bytes, char) file name
    (4 bytes, int) file position (position is absolute)
    (4 bytes, int) file lenght

    Data Store
    (N bytes, char) File data
*/

#define HEADER_SIZE 12
struct Header {
    char sig[PACK_FILE_SIG_LENGTH];
    int dirOffset;
    int dirLength;
};

#define DIRECTORY_ENTRY_SIZE 40
struct DirectoryEntry {
    char fileName[FILENAME_MAX_LENGTH];
    int filePosition;
    int fileLength;

    char* fileContents;
};

/**
* The PackageFile class is used to bundle files together in a single file on disk.
* 
* 
*
*/
class PackageFile
{
public:
    PackageFile();

    PackageFile(std::string packageFilePath);

    ~PackageFile();

    const char* GetFile(std::string filename, int& fileSize);

    PointerList<std::string>* GetAllFiles();

    void AddFile(std::string filename);

    void RemoveFile(std::string filename);

    void Save(std::string savePath);

private:
    Header* packageHeader;

    BaseList<std::string>* filesList;

    PointerList<DirectoryEntry*>* entries;

    FileContents* contents;

    std::string TargetPackage;

    std::string OutputFileName;

    /**
    * Read the package's directory and puts the list of Entries in the entries list.
    *
    * The data is not read at this point, only the file names and offsets. */
    void ReadPackage();
};

