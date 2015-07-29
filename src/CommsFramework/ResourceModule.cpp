#include "ResourceModule.h"



ResourceModule::ResourceModule()
{
    Resources = new PointerList<Resource*>();
}

ResourceModule::ResourceModule(std::string moduleName)
{
    ModuleName = moduleName;

    Resources = new PointerList<Resource*>();
}


ResourceModule::~ResourceModule()
{
    delete(Resources);
}

void ResourceModule::LoadResources()
{
}

void ResourceModule::UnloadResources()
{
}
