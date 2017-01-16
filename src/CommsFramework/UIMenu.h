#pragma once

class UIElement;
class MouseClickInfo;
class FPosition;
class GameEngine;
class BaseSprite;

#include "PointerList.h"
#include "FRectangle.h"


class UIMenu
{
public:
    UIMenu(GameEngine* engine);
    ~UIMenu();

    FPosition* MousePosition; // Relative to the 0,0 of the UIMenu.

    FRectangle MenuArea;


    virtual void Show();
    virtual void Hide();

    virtual void Update(MouseClickInfo* clickInfo);

    bool Visible;

protected:
    GameEngine* Engine;


    void AddElement(UIElement* newElement);
    void RemoveElement(UIElement* element);

    void RegisterBackgroundImageAndSetSize(BaseSprite* sprite);
private:
    BaseSprite* BackgroundImage;

    PointerList<UIElement*>* Elements;
};

