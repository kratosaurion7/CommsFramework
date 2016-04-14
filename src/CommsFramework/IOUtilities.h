#pragma once

class XFile;

#include <string>

#include "BaseList.h"

std::string GetLocalFileName(XFile* file);

BaseList<std::string>* GetFilePathComponents(XFile* file);

BaseList<std::string>* GetFilePathComponents(std::string path);

std::string GetFileExtension(XFile* file);

std::string GetParentDirectory(XFile* file);

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