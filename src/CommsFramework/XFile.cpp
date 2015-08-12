#include "XFile.h"



XFile::XFile()
{
	FileValid = false;
}

XFile::XFile(std::string name)
{
	FileValid = false;
	this->Open(name, XFILE_READ_WRITE);
}


XFile::~XFile()
{
}

void XFile::Open(std::string filePath, FILE_OPEN_MODE openMode, FILE_SHARE_MODE shareMode)
{
	int _accessMode = this->TranslateFileOpenMode(openMode);
	int _shareMode = this->TranslateFileShareMode(shareMode);

#ifdef _WINDOWS
	wchar_t wText[MAX_PATH];
	mbstowcs(wText, filePath.c_str(), filePath.length());

	HANDLE res = CreateFile(wText, _accessMode, _shareMode, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (res == INVALID_HANDLE_VALUE)
	{
		// Set error state or do stuff.
		FileValid = false;
		return;
	}

	winFileHandle = res;
#endif
}

void XFile::OpenCreate(std::string filePath, FILE_OPEN_CREATE_MODE createMode, FILE_SHARE_MODE shareMode)
{
	int _createMode = this->TranslateOpenCreateMode(createMode);
	int _shareMode = this->TranslateFileShareMode(shareMode);

#ifdef _WINDOWS
	wchar_t wText[MAX_PATH];
	mbstowcs(wText, filePath.c_str(), filePath.length());

	HANDLE res = CreateFile(wText, GENERIC_READ | GENERIC_WRITE, _shareMode, NULL, _createMode, FILE_ATTRIBUTE_NORMAL, NULL);

	if (res == INVALID_HANDLE_VALUE)
	{
		// Set error state or do stuff.
		FileValid = false;
		return;
	}

	winFileHandle = res;
#endif
}

void XFile::Close()
{
#ifdef _WINDOWS
	CloseHandle(winFileHandle);
#endif
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
