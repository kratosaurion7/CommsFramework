#pragma once

class GameEngine;
class BaseSprite;
class BaseText;

#include <string>

#include "Geometry/FPosition.h"

class EngineDialogMessage
{
public:
    EngineDialogMessage(GameEngine* engine);
    ~EngineDialogMessage();

    GameEngine* Engine;

    BaseSprite* DialogSprite;

    BaseText* DialogText;

    void Show(std::string message);
    void Show(std::string message, FPosition pos);

    void Close();

    bool IsOpen();

private:
    bool isOpen;
};