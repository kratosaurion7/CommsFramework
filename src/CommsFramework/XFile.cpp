#include "XFile.h"

#include "WindowsHelpers.h"

XFile::XFile()
{
	FileValid = false;
	FileSize = -1;
	FilePath = "";
}

XFile::XFile(std::string name)
{
	FileSize = -1;
	FileValid = false;
	FilePath = name;
}

XFile::~XFile()
{
}

void XFile::Open()
{
	if (FilePath != "")
	{
		this->Open(FilePath, XFILE_READ_WRITE);
	}
}

void XFile::Open(std::string filePath, FILE_OPEN_MODE openMode, FILE_SHARE_MODE shareMode)
{
	int _accessMode = this->TranslateFileOpenMode(openMode);
	int _shareMode = this->TranslateFileShareMode(shareMode);

	FilePath = filePath;

#ifdef _WINDOWS
	std::wstring wText = CStringToWideString(filePath);

	HANDLE res = CreateFile(wText.c_str(), _accessMode, _shareMode, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (res == INVALID_HANDLE_VALUE)
	{
		// Set error state or do stuff.
		FileValid = false;
		return;
	}

	winFileHandle = res;

	this->SetFileSize();
#endif
}

void XFile::OpenCreate()
{
	if (FilePath != "")
	{
		this->OpenCreate(FilePath, XCREATE_ALWAYS);
	}

}

void XFile::OpenCreate(std::string filePath, FILE_OPEN_CREATE_MODE createMode, FILE_SHARE_MODE shareMode)
{
	int _createMode = this->TranslateOpenCreateMode(createMode);
	int _shareMode = this->TranslateFileShareMode(shareMode);

#ifdef _WINDOWS
	wchar_t* wText = new wchar_t[filePath.length() + 1];
	mbstowcs(wText, filePath.c_str(), filePath.length() + 1);

	HANDLE res = CreateFile(wText, GENERIC_READ | GENERIC_WRITE, _shareMode, NULL, _createMode, FILE_ATTRIBUTE_NORMAL, NULL);

	if (res == INVALID_HANDLE_VALUE)
	{
		// Set error state or do stuff.
		FileValid = false;
		return;
	}

	winFileHandle = res;

	this->SetFileSize();
#endif
}

void XFile::Close()
{
#ifdef _WINDOWS
	CloseHandle(winFileHandle);
#endif
}

bool XFile::IsOpen()
{
#ifdef _WINDOWS
	return winFileHandle != INVALID_HANDLE_VALUE && FileValid;
#endif
}

FileContents * XFile::Read()
{
	if (!this->Check())
		return NULL;

	FileContents* contents = new FileContents();

#ifdef _WINDOWS
	char* buf = new char[FileSize];
	LPDWORD nbBytesRead = 0;
	LPOVERLAPPED overlap = new _OVERLAPPED();
	bool res = ReadFile(winFileHandle, buf, FileSize, nbBytesRead, overlap);
	
	if (res)
	{
		contents->buffer = buf;
		contents->fileSize = FileSize;
	}
	else 
	{
		DWORD err = GetLastError();
		// Error condition
		delete(contents);
		contents = NULL;
	}

#endif

	return contents;
}

void XFile::Read(char* &buf, int & size)
{
	if (!this->Check())
		return;

#ifdef _WINDOWS
	char* fileBuf = new char[FileSize];
	bool res = ReadFile(winFileHandle, fileBuf, FileSize, NULL, NULL);

	if (res)
	{
		buf = &(*fileBuf);
		size = FileSize;
	}
	else
	{
		DWORD err = GetLastError();
		// Error condition
	}

#endif
}

void XFile::Write(char * buf, int size)
{
	if (this->Check())
	{
#ifdef _WINDOWS
		bool res = WriteFile(winFileHandle, buf, size, NULL, NULL);

		if (!res)
		{
			DWORD err = GetLastError();
		}
#endif
	}
}

void XFile::CopyTo(std::string filePath)
{
	if (this->Check())
	{
#ifdef _WINDOWS
		wchar_t copyFromPath[MAX_PATH];
		mbstowcs(copyFromPath, FilePath.c_str(), FilePath.length());

		wchar_t copyToPath[MAX_PATH];
		mbstowcs(copyToPath, filePath.c_str(), filePath.length());

		bool res = CopyFile(copyFromPath, copyToPath, false);

		if (!res)
		{
			DWORD err = GetLastError();
			// Do error management
		}
#endif
	}
}

void XFile::MoveTo(std::string newPath)
{
	if (this->Check())
	{
#ifdef _WINDOWS
		wchar_t moveFromPath[MAX_PATH];
		mbstowcs(moveFromPath, FilePath.c_str(), FilePath.length());

		wchar_t moveToPath[MAX_PATH];
		mbstowcs(moveToPath, newPath.c_str(), newPath.length());

		bool res = MoveFile(moveFromPath, moveToPath);

		if (!res)
		{
			DWORD err = GetLastError();
			// Do error management
		}
#endif
	}
}

void XFile::Delete()
{
	if (this->Check())
	{
#ifdef _WINDOWS
		wchar_t wText[MAX_PATH];
		mbstowcs(wText, FilePath.c_str(), FilePath.length());

		this->Close();
		bool res = DeleteFile(wText);
		winFileHandle = NULL;
		FileValid = false;
#endif
	}
}

int XFile::TranslateFileOpenMode(FILE_OPEN_MODE mode)
{
#ifdef _WINDOWS
	switch (mode)
	{
	case XFILE_READ:
		return GENERIC_READ;
	case XFILE_WRITE:
		return GENERIC_WRITE;
	case XFILE_READ_WRITE:
		return GENERIC_READ | GENERIC_WRITE;
	default:
		return GENERIC_READ;
	}
#endif
}

int XFile::TranslateFileShareMode(FILE_SHARE_MODE mode)
{
#ifdef _WINDOWS
	switch (mode)
	{
	case XSHARE_MODE_NONE:
		return 0;
	case XSHARE_READ:
		return FILE_SHARE_READ;
	case XSHARE_WRITE:
		return FILE_SHARE_WRITE;
	default:
		return 0;
	}
#endif
}

int XFile::TranslateOpenCreateMode(FILE_OPEN_CREATE_MODE mode)
{
#ifdef _WINDOWS
	switch (mode)
	{
	case XCREATE_NEW:
		return CREATE_NEW;
	case XCREATE_ALWAYS:
		return CREATE_ALWAYS;
	case XOPEN_EXISTING:
		return OPEN_EXISTING;
	case XOPEN_ALWAYS:
		return OPEN_ALWAYS;
	case XTRUNCATE_EXISTING:
		return TRUNCATE_EXISTING;
	default:
		return CREATE_NEW;
	}
#endif
}

bool XFile::Check()
{
#ifdef _WINDOWS
	return winFileHandle != INVALID_HANDLE_VALUE;
#endif
}

void XFile::SetFileSize()
{
	if (this->Check())
	{
#ifdef _WINDOWS
		DWORD res = GetFileSize(winFileHandle, NULL);

		if (res == INVALID_FILE_SIZE)
		{
			FileSize = -1;
		}
		else
		{
			FileSize = res;
		}
#endif
	}
	else 
	{
		FileSize = -1;
	}
}

std::string GetFileNameFromFilePath(std::string filePath)
{
	return std::string();
}
