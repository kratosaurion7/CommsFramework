#include "GameSettings.h"



GameSettings::GameSettings()
{
    GameWindowTitle = "Down_Across";

    RegisterSetting((void*)&GameWindowHeight, "Game_Window_Height");
    RegisterSetting((void*)&GameWindowWidth, "Game_Window_Width");
    RegisterSetting((void*)&GameWindowTitle, "Game_Window_Title");

    RegisterSetting((void*)&TileHeight, "Tile_Height");
    RegisterSetting((void*)&TileWidth, "Tile_Width");

    RegisterSetting((void*)&GridRowsCount, "Grid_Row_Count");
    RegisterSetting((void*)&GridColumnsCount, "Grid_Column_Count");
}


GameSettings::~GameSettings()
{
}

void* GameSettings::ReadSetting(std::string name)
{
    return 0;
}
