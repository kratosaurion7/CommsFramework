#pragma once

class XFile;
class XDirectory;

#include <string>

#include "BaseList.h"

/*
 * This function returns the name of the file without the folders.
 */
std::string GetLocalFileName(XFile* file);

/*
 * Functions to return the 'components' of a path.
 * The components are the folders and the file making the path.
 */
BaseList<std::string>* GetFilePathComponents(XFile* file);
BaseList<std::string>* GetFilePathComponents(std::string path);

/*
 * Returns the extension of the file only, without the dot.
 */
std::string GetFileExtension(XFile* file);

/*
 * Returns the file name from the given path, without the extension.
 */
std::string GetFileName(std::string filePath);

/*
 * These functions can extract the parent directory of a specified
 * file or folder. They can get the directory name only or the full
 * path leading to the parent.
 */
std::string GetParentDirectoryPath(std::string path);
std::string GetParentDirectoryPath(XFile* file);

std::string GetParentDirectoryName(std::string path);
std::string GetParentDirectoryName(XFile* file);

XDirectory* GetParentDirectory(std::string path);
XDirectory* GetParentDirectory(XFile* file);

/*
 * This changes the filePath into a path that is canonically supported
 * by the OS. See the IsSanitizedFilePath function for more info.
 * See Also : https://msdn.microsoft.com/en-us/library/windows/desktop/aa365247%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
 */
std::string SanitizeFilePath(std::string filePath);

/*
 * This will check if the file path string is in a clean canonical format for
 * the current OS. For example on Windows this will change the slashes to
 * forward slashes and check to make sure that if the path is absolute there
 * will be a disk name at the front.
 */
bool IsSanitizedFilePath(std::string filePath);

/*
 * This tests if the file path is only valid and usable, 
 * it will still return true if the path is valid but not sanitized.
 */
bool IsValidFilePath(std::string filePath);

/*
 * Tests if the path is valid, could point to a directory or a file.
 */
bool IsValidPath(std::string path);

/*
 * Creates all the components of a path to make sure that the full path
 * is accesible. 
 */
void CreatePath(std::string path);