#include "Resource.h"

Resource::Resource(ResourceManager* resourceManagerPointer)
{
	_resourceManager = resourceManagerPointer;
}

Resource::~Resource()
{
	// Delete the data when deleting the Resource ?
}

char * Resource::GetData()
{
	return "a\0";
}
