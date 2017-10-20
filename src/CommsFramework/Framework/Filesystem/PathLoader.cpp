#include "PathLoader.h"

std::string PathLoader::basePath = "";

void PathLoader::SetBasePath(std::string basePath)
{
    // Probably need to sanitize the path or something
    PathLoader::basePath = basePath;
}

std::string PathLoader::GetPath(std::string pathLastPart)
{
    return PathLoader::basePath + pathLastPart;
}

PathLoader::PathLoader()
{
}


PathLoader::~PathLoader()
{
}
