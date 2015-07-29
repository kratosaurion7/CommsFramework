#pragma once

#include <string>

#include "ResourceManager.h"

enum ResourceType
{
    RES_IMG,
    RES_FONT,
    RES_AUDIO
};

class ResourceManager;

/**
	This class stores the data and metadata related to a game asset. The file data is loaded on demand
	and is kept as long as needed.

*/
class Resource
{
public:
    Resource(ResourceManager* resourceManagerPointer);
    ~Resource();

    std::string Name;

    ResourceType Type;

    std::string Format;

	char* GetData(int& dataSize, std::string targetModuleName = "");

private:
	int _dataSize;
	char* _dataCache;

	ResourceManager* _resourceManager;

    bool IsDataLoaded();

    void LoadDataFromStore();
};

