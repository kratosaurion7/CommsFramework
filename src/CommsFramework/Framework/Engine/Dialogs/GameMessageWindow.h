#pragma once

#include "Graphic/Base Classes/BaseSprite.h"
#include "Graphic/Base Classes/BaseText.h"
#include "Graphic/Base Classes/BaseTexture.h"
#include "Engine/GameEngine.h"

#include "Geometry/FPosition.h"
#include "Geometry/FRectangle.h"

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

