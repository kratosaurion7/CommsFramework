#include "SimpleMenu.h"

#include <GameEngine.h>

SimpleMenu::SimpleMenu(GameEngine* engine) : UIMenu::UIMenu(engine)
{
    BaseSprite* btnOneActiveState = engine->CreateSprite("Menu\\Button_Active.png");
    BaseSprite* btnOneDisabledState = engine->CreateSprite("Menu\\Button_Disabled.png");
    BaseSprite* btnOneHoverState = engine->CreateSprite("Menu\\Button_Hover.png");
    BaseSprite* btnOnePushedState = engine->CreateSprite("Menu\\Button_Pushed.png");

    BaseSprite* menuBackground = engine->CreateSprite("Menu\\MenuBackground.png");

    ButtonOne = new UIButton(btnOneActiveState);
    MenuBackground = menuBackground;

    this->AddElement(ButtonOne);
    
    this->RegisterBackgroundImageAndSetSize(menuBackground);
}


SimpleMenu::~SimpleMenu()
{
}
