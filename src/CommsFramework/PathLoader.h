#pragma once

#include <string>

class PathLoader
{
public:
    static void SetBasePath(std::string basePath);

    static std::string GetPath(std::string pathLastPart);

private:
    static std::string basePath;

    PathLoader();
    ~PathLoader();
};

