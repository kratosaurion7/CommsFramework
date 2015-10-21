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

PointerList<std::string>* GameSettings::GetSettingsList()
{
    PointerList<std::string>* settings = new PointerList<std::string>();

    settings->Add(std::to_string(GameWindowHeight));
    settings->Add(std::to_string(GameWindowHeight));
    settings->Add(std::to_string(GameWindowHeight));

    settings->Add(std::to_string(TileHeight));
    settings->Add(std::to_string(TileWidth));

    settings->Add(std::to_string(GridRowsCount));
    settings->Add(std::to_string(GridColumnsCount));

    return settings;
}