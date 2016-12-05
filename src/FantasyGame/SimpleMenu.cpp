#include "SimpleMenu.h"

#include <GameEngine.h>
#include <BaseSprite.h>

SimpleMenu::SimpleMenu(GameEngine* engine) : UIMenu::UIMenu(engine)
{
    //BaseSprite* btnOneActiveState = engine->CreateSprite("1", "Menu\\Button_Active.png");
    BaseSprite* btnOneActiveState = engine->CreateSprite();
    btnOneActiveState->SetTextureName("Assets\\Menu\\Button_Active.png");
    
    BaseSprite* btnOneDisabledState = engine->CreateSprite("2", "Assets\\Menu\\Button_Disabled.png");
    BaseSprite* btnOneHoverState = engine->CreateSprite("3", "Assets\\Menu\\Button_Hover.png");
    BaseSprite* btnOnePushedState = engine->CreateSprite("4", "Assets\\Menu\\Button_Pushed.png");

    BaseSprite* menuBackground = engine->CreateSprite("5", "Assets\\Menu\\MenuBackground.png");

    ButtonOne = new UIButton(btnOneActiveState);
    MenuBackground = menuBackground;

    this->AddElement(ButtonOne);
    
    this->RegisterBackgroundImageAndSetSize(menuBackground);
}


SimpleMenu::~SimpleMenu()
{
}
