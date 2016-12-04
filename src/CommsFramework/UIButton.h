#pragma once

#include "UIElement.h"

class BaseSprite;

class UIButton : public UIElement
{
public:
    UIButton(BaseSprite* activeSprite = NULL, BaseSprite* disabledSprite = NULL, BaseSprite* pushedSprite = NULL, BaseSprite* hoverSprite = NULL);
    ~UIButton();

    BaseSprite* ActiveButtonSprite;
    BaseSprite* DisabledButtonSprite;
    BaseSprite* PushedButtonSprite;
    BaseSprite* HoverButtonSprite;

    bool IsDisabled;

    virtual void Show();
    virtual void Hide();

    virtual void Update(MouseClickInfo* mouseInfo);
};

