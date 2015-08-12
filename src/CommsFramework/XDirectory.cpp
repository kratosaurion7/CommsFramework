#include "XDirectory.h"



XDirectory::XDirectory()
{
}

XDirectory::XDirectory(std::string path)
{
	FullPath = path;

	this->OpenDirectory();
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
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(dirPath, &ffd);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		// Do error management
		return NULL;
	}

	do 
	{
		bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

		if (!isDirectory)
		{
			WCHAR* x = ffd.cFileName;

			char defChar = ' ';
			char* filePath = new char[MAX_PATH];

			WideCharToMultiByte(CP_ACP, 0, x, -1, filePath, MAX_PATH, &defChar, NULL);


			XFile* newFile = new XFile(filePath);
			if (newFile->FileValid)
			{
				ret->Add(newFile);
			}
		}
		else
		{
			if (recursive)
			{
				// Recurse into new directory.
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
#endif

	return ret;
}

PointerList<XDirectory*>* XDirectory::GetDirectories(bool recursive)
{
	PointerList<XDirectory*>* ret = new PointerList<XDirectory*>();

#ifdef _WINDOWS
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(dirPath, &ffd);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		// Do error management
		return NULL;
	}

	do
	{
		bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

		if (isDirectory)
		{
			WCHAR* x = ffd.cFileName;

			char defChar = ' ';
			char* filePath = new char[MAX_PATH];

			WideCharToMultiByte(CP_ACP, 0, x, -1, filePath, MAX_PATH, &defChar, NULL);

			XDirectory* newDir = new XDirectory(filePath);

			if (newDir->Check())
			{
				ret->Add(newDir);
			}
		}
		else
		{
			if (recursive)
			{
				// Recurse into new directory.
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
#endif
	return ret;
}

bool XDirectory::Check()
{
#ifdef _WINDOWS
	return FullPath != "" && winDirHandle != INVALID_HANDLE_VALUE;
#endif
}

void XDirectory::OpenDirectory()
{

}

XDirectory * GetWorkingDir()
{
	return nullptr;
}

void ChangeWorkingDir(std::string newPath)
{
}
