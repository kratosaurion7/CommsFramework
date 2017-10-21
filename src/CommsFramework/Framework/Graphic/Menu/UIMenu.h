#pragma once

class UIElement;
struct MouseClickInfo;
class FPosition;
class GameEngine;
class BaseSprite;

class UIButton;
class UIImage;

#include "Collections/PointerList.h"
#include "Geometry/FRectangle.h"


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

    UIImage* CreateImage(std::string imagePath);
    UIButton* CreateButton(std::string idleImage, std::string disabled = "", std::string pushed = "", std::string hovered = "");

    void AddElement(UIElement* newElement);
    void RemoveElement(UIElement* element);

    void RegisterBackgroundImageAndSetSize(BaseSprite* sprite);
private:
    BaseSprite* BackgroundImage;

    PointerList<UIElement*>* Elements;
};

