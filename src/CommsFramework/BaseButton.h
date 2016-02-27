#pragma once

#include "BaseList.h"
#include "PointerList.h"

class BaseSprite;

class BaseButton
{
public:
    BaseButton();
    ~BaseButton();

    bool IsDown();

    bool IsClicked();

};

