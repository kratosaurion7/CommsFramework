#pragma once

#include <string>

#include "Resource.h"
#include "PackageFile.h"

class Resource;

enum ContainerTypes {
	CONTAINER_TYPE_PACKAGE,
	CONTAINER_TYPE_FOLDER
};

class ResourceContainer
{
public:
	ResourceContainer();
	~ResourceContainer();

	std::string Name;

	ContainerTypes ContainerType;

	bool Contains(Resource* resource);

	const char* LoadData(Resource* resource, int& size);

private:
	//PackageFile* pack;

	bool Package_Contains(Resource* res);

	bool Folder_Contains(Resource* res);

};

