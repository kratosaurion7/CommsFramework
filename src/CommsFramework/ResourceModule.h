#pragma once

#include <string>

#include "Resource.h"

#include "PointerList.h"

class Resource;

class ResourceModule
{
public:
    ResourceModule();
    ResourceModule(std::string moduleName);
    ~ResourceModule();

    std::string ModuleName;

    PointerList<Resource*>* Resources;

    void LoadResources();

    void UnloadResources();
};

