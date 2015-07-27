#pragma once

#include <string>

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
};

