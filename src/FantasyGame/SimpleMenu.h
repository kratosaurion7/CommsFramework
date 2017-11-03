#pragma once

#include <Graphic/Menu/UIMenu.h>
#include <Graphic/Menu/UIElement.h>
#include <Graphic/Menu/UIButton.h>

class BaseSprite;
class GameEngine;

class SimpleMenu : public UIMenu
{
public:
    SimpleMenu(GameEngine* engine);
    ~SimpleMenu();

    UIButton* ButtonOne;

    BaseSprite* MenuBackground;
};

