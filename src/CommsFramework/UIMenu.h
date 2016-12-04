#pragma once
#include "PointerList.h"

class UIElement;
class MouseClickInfo;

class UIMenu
{
public:
    UIMenu();
    ~UIMenu();

    virtual void Show();
    virtual void Hide();

    virtual void Update(MouseClickInfo* clickInfo);

    FPosition* MousePosition; // Relative to the 0,0 of the UIMenu.

protected:

    void AddElement(UIElement* newElement);
    void RemoveElement(UIElement* element);

private:

    PointerList<UIElement*>* Elements;
};

