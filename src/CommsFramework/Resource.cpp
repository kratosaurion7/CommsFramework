#include "Resource.h"

Resource::Resource(ResourceManager* resourceManagerPointer)
{
	_resourceManager = resourceManagerPointer;
}

Resource::~Resource()
{
	// Delete the data when deleting the Resource ?
}

char* Resource::GetData(int& dataSize, std::string targetModuleName)
{
    if (_dataCache == NULL)
    {
        _dataCache = _resourceManager->GetResourceDataFromStore(this, dataSize, targetModuleName);

        _dataSize = dataSize;

        return _dataCache;
    }
    else 
    {
        // And check if invalid cache I guess.
        dataSize = dataSize;
        return _dataCache;
    }
}

bool Resource::IsDataLoaded()
{
    return _dataCache != NULL;
}

void Resource::LoadDataFromStore()
{
}
