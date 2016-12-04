#pragma once

#include "UIElement.h"

class BaseSprite;

class UIButton : public UIElement
{
public:
    enum UIButtonState
    {
        ACTIVE,
        HOVERED,
        PUSHED,
        CLICKED,
        DISABLED
    };

    UIButton(BaseSprite* activeSprite = NULL, BaseSprite* disabledSprite = NULL, BaseSprite* pushedSprite = NULL, BaseSprite* hoverSprite = NULL);
    ~UIButton();

    BaseSprite* ActiveButtonSprite;
    BaseSprite* DisabledButtonSprite;
    BaseSprite* PushedButtonSprite;
    BaseSprite* HoverButtonSprite;

    UIButtonState CurrentState;

    bool Clicked;
    bool IsDisabled;

    virtual void Show();
    virtual void Hide();
    virtual void Reset();

    virtual void Update(MouseClickInfo* mouseInfo);
};