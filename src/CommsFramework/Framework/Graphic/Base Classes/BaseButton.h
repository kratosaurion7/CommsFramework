#pragma once

#include "Collections/BaseList.h"
#include "Collections/PointerList.h"

class BaseSprite;

class BaseButton
{
public:
    BaseButton();
    ~BaseButton();

    bool IsDown();

    bool IsClicked();

};

