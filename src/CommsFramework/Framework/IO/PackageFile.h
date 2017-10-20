#pragma once

class XFile;
class XDirectory;
class EncryptedPackageFile;

#include <cstdio>
#include <string>

#include "FileReader.h"
#include "PointerList.h"

#define FILENAME_MAX_LENGTH 256
#define PACK_FILE_SIG_LENGTH 4

/*
    =Format=
    Header
    (4 bytes) signature = 'PACK'
    (4 bytes, int) offset to start of directory (offset is absolute)
    (4 bytes, int) directory lenght

    Directory entries
    (256 bytes, char) file name
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

#define DIRECTORY_ENTRY_SIZE 264
struct DirectoryEntry {
    char fileName[FILENAME_MAX_LENGTH];
    int filePosition;
    int fileLength;

    char* fileContents;
};

/** \brief The PackageFile class is used to bundle files together that can be extracted afterwards.
*			The empty constructor is used to initiate a blank package where files can be added. 
*			The second constructor PackageFile(string) is used to specify an existing package file
*			that is used to extract files from.
* 
* ========== Overview ==========
*
* PackageFile is implementing the PACK format from Quake. The format spec can be found in the "docs/pak.txt"
*  directory. The basic packaging algorithm is such : each time a file is added to the package an entry is created and 
*  added to the entries list, each entry is of type DirectoryEntry. The contents of the files are not yet retrieved from disk
*  so the class never really grows big until a Save() is called. When the Save() function is called, the PAK directory is build
*  using the information from the entries list. After the directory is build, the content of each file is read into a memory stream
*  (of type std::stringstream). In fact, all writes so far are first done into a memory stream. When all files are loaded the stream is 
*  written to disk.
*
* Directories can be added add all the sub-files of that directory. The directory tree will be preserved when extracting the package.
* Each file keeps his path relative to the directory when added and will appear inside the same sub-folders when the package is extracted.
* This is done by doing a path difference between the file and the added directory, this results in each file keeping a relative path to its
* "mother" directory.
*
* ========== Inputs ==========
*
* Adding files is the means of input for the PackageFile class. Adding a file is done either by passing a path or an instance of XFile.
* One can also add directories, either by path or by passing a XDirectory. All files in the directory tree (recursively) are added.
* Adding a directory causes each sub-file to be added respectively of it's position inside the added directory.
*
* ========== Outputs ==========
*
* ========== Dependencies ==========
*
* FileReader
* PointerList

*/
class PackageFile
{
public:
    PackageFile();

	/**
		Constructor used to open an existing package. 

		This constructor needs to be used because there is no function Load(packagePath).
	*/
    PackageFile(std::string packageFilePath);

    ~PackageFile();

    virtual const char* GetFile(std::string filename, int& fileSize);

    PointerList<std::string>* GetAllFiles();

    void AddFile(std::string filename);
    void AddFile(XFile* file);

    void AddDirectory(std::string directoryPath);
    void AddDirectory(XDirectory* directory);

    void RemoveFile(std::string filename);

    EncryptedPackageFile* SaveEncrypt(std::string savePath, char* key);

    virtual void Save(std::string savePath);

    virtual void Extract(std::string outPath);

protected:

    virtual void AddFile(std::string filename, std::string directoryRoot);

    /**
    * Read the package's directory and puts the list of Entries in the entries list.
    *
    * The data is not read at this point, only the file names and offsets. */
    virtual void ReadPackage();

    virtual void ReadBytes(char* targetBuffer, int nbBytes, std::iostream* stream);

    virtual void WriteBytes(char* targetBuffer, int nbBytes, std::iostream* stream);

    struct FileListEntry
    {
        XFile* File;

        std::string RelativeDirectoryParentRoot;
    };

    /*
     * Indicate that the package has been read from disk after creating the PackageFile instance.
     *  If false, the function ReadPackage needs to be called to load the entries.
     */
    bool packageRead; 

    Header* packageHeader;

    PointerList<FileListEntry*>* filesList;

    PointerList<DirectoryEntry*>* entries;

    FileContents* contents;

    std::string TargetPackage;

    std::string OutputFileName;

    std::iostream* memStream;
};

