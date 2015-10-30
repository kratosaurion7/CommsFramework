#pragma once

#include "BaseSprite.h"
#include "GameEngine.h"
#include "FPosition.h"

class EngineDialogMessage
{
public:
    EngineDialogMessage(GameEngine* engine);
    ~EngineDialogMessage();

    GameEngine* Engine;

    BaseSprite* DialogSprite;

    BaseText* DialogText;

    void Show();
    void Show(FPosition pos);

    void Close();

    bool IsOpen();

private:
    bool isOpen;
};