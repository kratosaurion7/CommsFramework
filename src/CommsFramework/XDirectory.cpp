#include "XDirectory.h"

#include <memory>


XDirectory::XDirectory()
{
}

XDirectory::XDirectory(std::string path)
{
	FullPath = path;
    mbstowcs(dirPath, path.c_str(), path.length() + 1);
}


XDirectory::~XDirectory()
{
}

XDirectory * XDirectory::OpenDirectory(std::string path)
{
	XDirectory* dir = new XDirectory(path);

	if (dir->Check())
	{
		return dir;
	} else
	{
		return NULL;
	}
}

PointerList<XFile*>* XDirectory::GetFiles(bool recursive)
{
    PointerList<XFile*>* ret = new PointerList<XFile*>();

#ifdef _WINDOWS

    this->FindFilesInDirectory(dirPath, *ret, recursive);

#endif
    return ret;
}

PointerList<XDirectory*>* XDirectory::GetDirectories(bool recursive)
{
    return NULL;
}

bool XDirectory::Check()
{
#ifdef _WINDOWS
	return FullPath != "";
#endif
}

void XDirectory::FindFilesInDirectory(wchar_t* directoryPath, PointerList<XFile*> &filesAggregate, bool recursive)
{
#ifdef _WINDOWS
    WIN32_FIND_DATA ffd;

	std::wstring directorySearchAlias = directoryPath;
	directorySearchAlias.append(_T("\\*"));

    HANDLE hFind = FindFirstFile(directorySearchAlias.c_str(), &ffd);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        // Do error management
        return;
    }

    do {
		if (IsDotFile(ffd));
            continue;

        bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        
        if (isDirectory && recursive)
        {
            wchar_t* subDirectoryPath = new wchar_t[lstrlenW(directoryPath) + lstrlenW(ffd.cFileName) + 5];

            wsprintfW(subDirectoryPath, _T("%s\\%s"), directoryPath, ffd.cFileName);

            FindFilesInDirectory(subDirectoryPath, filesAggregate, recursive);
        }
        else
        {
            WCHAR* x = ffd.cFileName;

            char defChar = ' ';
            char* filePath = new char[MAX_PATH];

            WideCharToMultiByte(CP_ACP, 0, x, -1, filePath, MAX_PATH, &defChar, NULL);

            XFile* newFile = new XFile(filePath);
            filesAggregate.Add(newFile);
        }

    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);

#endif
}

XDirectory * GetWorkingDir()
{
	return nullptr;
}

void ChangeWorkingDir(std::string newPath)
{
}

bool IsDotFile(WIN32_FIND_DATA dir)
{
	return lstrcmpW(currentDotDirName, dir.cFileName) == 0 || lstrcmpW(parentDotDirName, dir.cFileName) == 0;
}
