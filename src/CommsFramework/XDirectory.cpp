#include "XDirectory.h"

#include <memory>

#include "WindowsHelpers.h" // TODO : REplace that by a generic header, these functions are not specific to windows


XDirectory::XDirectory(std::string path)
{
	FullPath = path;

	DirectoryPath = CStringToWideString(path);
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

    this->FindFilesInDirectory(DirectoryPath.c_str(), *ret, recursive);

#endif
    return ret;
}

PointerList<XDirectory*>* XDirectory::GetDirectories(bool recursive)
{
    return NULL;
}

#ifdef _WINDOWS
XDirectory::XDirectory(std::wstring path)
{
	FullPath = WideStringToCString(path);
}

XDirectory * XDirectory::OpenDirectory(std::wstring path)
{
	XDirectory* dir = new XDirectory(path);

	if (dir->Check())
	{
		return dir;
	}
	else
	{
		return NULL;
	}
}
#endif

bool XDirectory::Check()
{
#ifdef _WINDOWS
	return FullPath != "";
#elif
	return false;
#endif
}

void XDirectory::FindFilesInDirectory(std::wstring directoryPath, PointerList<XFile*> &filesAggregate, bool recursive)
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
		if (IsDotFile(ffd))
            continue;

        bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        
        if (isDirectory && recursive)
        {
			// Fix line to not append directly to the same string buffer.
			//std::wstring subDirectoryPath = directoryPath.append(_T("\\")).append(ffd.cFileName);

            wchar_t* subDirectoryPath = new wchar_t[directoryPath.length() + lstrlenW(ffd.cFileName)];

            wsprintfW(subDirectoryPath, _T("%s\\%s"), directoryPath.c_str(), ffd.cFileName);

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

XDirectory* GetWorkingDir()
{
#ifdef _WINDOWS
	wchar_t* buf[MAX_PATH];
	DWORD res = GetCurrentDirectory(MAX_PATH, *buf);

	if (res == 0)
	{
		DWORD err = GetLastError();

		return NULL;
	}


	XDirectory* currentDir = XDirectory::OpenDirectory(*buf);

	return currentDir;
#elif
	return NULL;
#endif
}

void ChangeWorkingDir(std::string newPath)
{
#ifdef _WINDOWS
	wchar_t* dirPath[MAX_PATH];
	mbstowcs(*dirPath, newPath.c_str(), newPath.length() + 1);

	bool res = SetCurrentDirectory(*dirPath);

	if (res == 0)
	{
		DWORD err = GetLastError();
	}
#endif
}

#ifdef _WINDOWS
bool IsDotFile(WIN32_FIND_DATA dir)
{
	auto x = lstrcmpW(currentDotDirName, dir.cFileName);
	auto y = lstrcmpW(parentDotDirName, dir.cFileName);

	return (x == 0) || (y == 0);
}
#endif