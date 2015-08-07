#pragma once

#include <stdio.h>
#include <fstream>

#include <string>

void DumpData(const char* data, int size);


//void FileReader::DumpFile(std::string outFileName)
//{
//	fileStream->seekg(0, 0);
//
//	std::ofstream outStream = std::ofstream(outFileName.c_str(), std::ofstream::out | std::ofstream::binary);
//
//	int fileSize = GetFileSize();
//
//	char* contents = new char[fileSize];
//
//	fileStream->read(contents, fileSize);
//
//	outStream.write(contents, fileSize);
//
//	delete(contents);
//
//	outStream.close();
//
//	fileStream->seekg(0, 0);
//}
