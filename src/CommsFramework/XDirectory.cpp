#include "XDirectory.h"



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
	return FullPath != "" && winDirHandle != INVALID_HANDLE_VALUE;
#endif
}

void XDirectory::FindFilesInDirectory(wchar_t* directoryPath, PointerList<XFile*> &filesAggregate, bool recursive)
{
#ifdef _WINDOWS
    WIN32_FIND_DATA ffd;

    wchar_t* directorySearchAlias = new wchar_t[lstrlenW(directoryPath) + 4];

    //auto aliasDirectoryName = lstrcatW(directorySearchAlias, _T("\\*"));
    lstrcpyW(directorySearchAlias, directoryPath);
    lstrcatW(directorySearchAlias, _T("\\*"));

    HANDLE hFind = FindFirstFile(directorySearchAlias, &ffd);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        // Do error management
        return;
    }

    do {
        if (lstrcmpW(ffd.cFileName, currentDirName) == 0 || lstrcmpW(ffd.cFileName, parentDirName) == 0)
            continue;

        bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        
        if (isDirectory && recursive)
        {
            //wchar_t* buf = new wchar_t[MAX_PATH];
            //DWORD res = GetFinalPathNameByHandle(hFind, buf, MAX_PATH, FILE_NAME_NORMALIZED);

            wchar_t* subDirectoryPath = new wchar_t[lstrlenW(directoryPath) + lstrlenW(ffd.cFileName) + 5];
            lstrcpyW(subDirectoryPath, directoryPath);
            lstrcatW(subDirectoryPath, _T("\\"));
            lstrcatW(subDirectoryPath, ffd.cFileName);
            lstrcatW(subDirectoryPath, _T("\0"));

            //wchar_t* expanded = lstrcatW(ffd.cFileName, _T("\\*"));

            //wchar_t* dirWithSlash = lstrcatW(directoryPath, _T("\\"));

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
