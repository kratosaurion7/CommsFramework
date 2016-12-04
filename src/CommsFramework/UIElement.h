#pragma once

class BaseSprite;
class UIMenu;
class FPosition;
class MouseClickInfo;

#include "PointerList.h"

class UIElement
{
public:
    UIElement();
    ~UIElement();

    virtual void Show();
    virtual void Hide();

    virtual void Update(MouseClickInfo* mouseInfo);

protected:
    PointerList<BaseSprite*>* ElementSprites;

    UIMenu* Owner;
};

