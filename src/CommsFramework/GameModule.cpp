#include "GameModule.h"



GameModule::GameModule()
{
    Resources = new PointerList<Resource*>();
}

GameModule::GameModule(std::string moduleName)
{
    ModuleName = moduleName;

    Resources = new PointerList<Resource*>();
}


GameModule::~GameModule()
{
    delete(Resources);
}

void GameModule::LoadResources()
{
}

void GameModule::UnloadResources()
{
}
