#pragma once

class BaseSprite;
class UIMenu;
class FPosition;
struct MouseClickInfo;

#include "Collections/PointerList.h"

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