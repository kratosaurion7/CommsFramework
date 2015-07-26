#pragma once

#include <string>

#include "FileReader.h"

#include "BaseList.h"

#include "XmlReader.h"

class ResourceManager
{
public:
	ResourceManager(std::string configFile);
	~ResourceManager();

    void ParseConfigFiles();

private:
    FileContents* configFileContents;
	
    std::string configFileLocation;

    BaseList<std::string>* secondaryConfigFiles;

};

