#pragma once

#include <SettingsRepository.h>

#include <string>

class GameSettings : public SettingsRepository
{
public:
    GameSettings();
    ~GameSettings();
    
    // GAME WINDOW SETTINGS
    const int GameWindowHeight = 600;
    const int GameWindowWidth = 600;
    std::string GameWindowTitle = "aaa";

    // GAME TILES SETTINGS
    const int TileHeight = 64;
    const int TileWidth = 64;

    // GAME GRID SETTINGS
    const int GridRowsCount = 5;
    const int GridColumnsCount = 5;

    const bool GridIsSquare = true;
};

