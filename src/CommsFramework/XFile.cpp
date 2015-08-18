#include "XFile.h"

#include "WindowsHelpers.h"

#include <assert.h>

XFile::XFile(std::string name)
{
	FileSize = -1;
	FileValid = false;
	FilePath = name;
	parentDir = NULL;

	if (this->Open())
	{
		this->Exists = true;
		this->FileValid = true;

		this->CreateAndAssignPathInfo();
	}
	
}

XFile::~XFile()
{
	delete(parentDir);
}

bool XFile::Open()
{
	if (FilePath != "")
	{
		return this->Open(XFILE_READ_WRITE);
	}
	else 
	{
		return false;
	}
}

bool XFile::Open(FILE_OPEN_MODE openMode, FILE_SHARE_MODE shareMode)
{
	int _accessMode = this->TranslateFileOpenMode(openMode);
	int _shareMode = this->TranslateFileShareMode(shareMode);

#ifdef _WINDOWS
	std::wstring wText = CStringToWideString(FilePath);

	HANDLE res = CreateFile(wText.c_str(), _accessMode, _shareMode, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (res == INVALID_HANDLE_VALUE)
	{
		// Set error state or do stuff.
		FileValid = false;
		return false;
	}

	winFileHandle = res;

	this->AssignFileSize();
#endif

	return true;
}

bool XFile::OpenCreate()
{
	if (FilePath != "")
	{
		return this->OpenCreate(XCREATE_ALWAYS);
	}
	else
	{
		return false;
	}
}

bool XFile::OpenCreate(FILE_OPEN_CREATE_MODE createMode, FILE_SHARE_MODE shareMode)
{
	int _createMode = this->TranslateOpenCreateMode(createMode);
	int _shareMode = this->TranslateFileShareMode(shareMode);

#ifdef _WINDOWS
	wchar_t* wText = new wchar_t[FilePath.length() + 1];
	mbstowcs(wText, FilePath.c_str(), FilePath.length() + 1);

	HANDLE res = CreateFile(wText, GENERIC_READ | GENERIC_WRITE, _shareMode, NULL, _createMode, FILE_ATTRIBUTE_NORMAL, NULL);

	if (res == INVALID_HANDLE_VALUE)
	{
		// Set error state or do stuff.
		FileValid = false;
		return false;
	}

	winFileHandle = res;

	this->AssignFileSize();
#endif

	return true;
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

void XFile::AppendText(char * text, int size)
{
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
	
	delete(overlap);

#endif

	return contents;
}

void XFile::Read(char* &buf, int & size)
{
	if (!this->Check())
		return;

#ifdef _WINDOWS
	char* fileBuf = new char[FileSize];
	LPDWORD nbBytesRead = 0;
	LPOVERLAPPED overlap = new _OVERLAPPED();
	bool res = ReadFile(winFileHandle, fileBuf, FileSize, nbBytesRead, overlap);

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

	delete(overlap);

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

XDirectory * XFile::ParentDirectory()
{
	if (parentDir == NULL)
	{
		if (ParentDirectoryPath != "")
		{
			XDirectory* parent = new XDirectory(ParentDirectoryPath);
			
			parentDir = parent;

			return parentDir;
		}
	}
	else
	{
		return parentDir;
	}

	return NULL;
}

void XFile::CopyTo(std::string filePath, bool overwrite)
{
	if (this->Check())
	{
#ifdef _WINDOWS
		std::wstring copyFromPath = CStringToWideString(FilePath);

		std::wstring copyToPath = CStringToWideString(filePath);

		this->Close();

		bool res = CopyFile(copyFromPath.c_str(), copyToPath.c_str(), overwrite);

		if (!res)
		{
			DWORD err = GetLastError();
			// Do error management
		}
#endif
	}
}

void XFile::CopyTo(XDirectory * targetDir, bool overwrite)
{
	std::string destination = targetDir->FullPath.append("//").append(this->FileName);

	this->CopyTo(destination, overwrite);
}

void XFile::MoveTo(std::string filePath, bool overwrite)
{
	if (this->Check())
	{
#ifdef _WINDOWS
		std::wstring moveFromPath = CStringToWideString(FilePath);

		std::wstring moveToPath = CStringToWideString(filePath);

		DWORD moveOptions = overwrite == true ? MOVEFILE_REPLACE_EXISTING : 0;

		this->Close();

		bool res = MoveFileEx(moveFromPath.c_str(), moveToPath.c_str(), moveOptions);

		if (res)
		{
			FilePath = filePath;

			this->Open();
		}
		else 
		{
			DWORD err = GetLastError();
			// Do error management
		}
#endif
	}
}

void XFile::MoveTo(XDirectory * targetDir, bool overwrite)
{
	std::string destination = targetDir->FullPath.append("//").append(this->FileName);

	this->MoveTo(destination, overwrite);
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

void XFile::CreateAndAssignPathInfo()
{
	if (this->IsOpen() && this->Exists)
	{
#ifdef _WINDOWS
		// Here I have a valid handle and the file exists
		TCHAR path[MAX_PATH];
		DWORD res;

		res = GetFinalPathNameByHandle(winFileHandle, path, MAX_PATH, VOLUME_NAME_DOS);

		if (res < MAX_PATH)
		{
			std::string _fileName;
			std::string _parentDirPath;
			std::string _fileExt;


			std::wstring x = path;
			std::string y = WideStringToCString(x);

			int lastSlash = y.find_last_of("\\");

			_fileName = y.substr(lastSlash + 1, y.length() - lastSlash);

			_parentDirPath = y.substr(0, lastSlash);

			int fileNameExtensionDot = _fileName.find_last_of(".");
			_fileExt = _fileName.substr(fileNameExtensionDot, _fileName.length() - fileNameExtensionDot);

			FileName = _fileName;
			FileExt = _fileExt;
			
			ParentDirectoryPath = CleanupDirectoryName(_parentDirPath);
		}
		else
		{
			// Path too big ?
			assert(true);
		}

#endif
	}
	else 
	{
		// Path is relative,probably
	}
}

std::string XFile::CleanupDirectoryName(std::string stringToClean)
{
	// On windows, the GetFinalPathNameByHandle return the path using the \\?\ (convention to mark the path as unicode to support 32k char paths)
	return stringToClean.substr(4, stringToClean.length() - 4);
}

bool XFile::Check()
{
#ifdef _WINDOWS
	return winFileHandle != INVALID_HANDLE_VALUE;
#endif
}

__int64 XFile::GetSize()
{
	if (this->Check())
	{
#ifdef _WINDOWS
		PLARGE_INTEGER fileSize;

		bool res = GetFileSizeEx(winFileHandle, fileSize);

		if (res != 0)
		{
			return fileSize->QuadPart;
		}
		else {
			DWORD err = GetLastError();

			// Check error
		}
#endif
	}

	return -1;
}

void XFile::AssignFileSize()
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
