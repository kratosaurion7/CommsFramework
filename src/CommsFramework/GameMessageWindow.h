#pragma once

#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseTexture.h"
#include "GameEngine.h"

#include "FPosition.h"
#include "FRectangle.h"

class GameMessageWindow
{
public:
    GameMessageWindow();
    ~GameMessageWindow();

    BaseSprite* WindowSprite;
    BaseText* WindowText;

    bool IsOpen;

    void SetDialogPosition(FPosition pos);

    void Show();

    void Close();
};

