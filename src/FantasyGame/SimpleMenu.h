#pragma once

#include <UIMenu.h>
#include <UIElement.h>
#include <UIButton.h>

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

