#include "XDirectory.h"



XDirectory::XDirectory()
{
}


XDirectory::~XDirectory()
{
}

XDirectory * XDirectory::OpenDirectory(std::string path)
{
	return nullptr;
}

std::string XDirectory::Name()
{
	return std::string();
}

std::string XDirectory::FullPath()
{
	return std::string();
}

PointerList<XFile*>* XDirectory::GetFiles(bool recursive)
{
	return nullptr;
}

PointerList<XDirectory*>* XDirectory::GetDirectories(bool recursive)
{
	return nullptr;
}

XDirectory * GetWorkingDir()
{
	return nullptr;
}

void ChangeWorkingDir(std::string newPath)
{
}
