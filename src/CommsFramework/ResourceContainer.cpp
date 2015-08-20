#include "ResourceContainer.h"

#include "Utilities.h"

ResourceContainer::ResourceContainer()
{
    //pack = new PackageFile(Name);
}


ResourceContainer::~ResourceContainer()
{
    //delete(pack);
}

bool ResourceContainer::Contains(Resource* resource)
{
    if (ContainerType == CONTAINER_TYPE_PACKAGE)
    {
        return Package_Contains(resource);
    }
    else if (ContainerType == CONTAINER_TYPE_FOLDER)
    {
        return Folder_Contains(resource);
    }

    return false;
}

const char * ResourceContainer::LoadData(Resource * resource, int& dataSize)
{
    PackageFile pack(Name);

    // TODO : SUPPORT RELATIVE PATH NAMES ?
    //std::string fileName = "assets\\" + resource->Name + "." + resource->Format;
    std::string fileName = resource->Name + "." + resource->Format;
    const char* x = pack.GetFile(fileName, dataSize);

    return x;
}

bool ResourceContainer::Package_Contains(Resource * res)
{
    PackageFile pack(Name);

    int fileSize = 0;
    // TODO : SUPPORT RELATIVE FILE NAMES
    //std::string fileName = "assets\\" + res->Name + "." + res->Format;
    std::string fileName = res->Name + "." + res->Format;
    const char* x = pack.GetFile(fileName, fileSize);

    bool result = x != NULL;

    delete(x);

    return result;
}

bool ResourceContainer::Folder_Contains(Resource * res)
{
    return false;
}
