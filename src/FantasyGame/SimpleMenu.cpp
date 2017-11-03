#include "SimpleMenu.h"

#include <Engine/GameEngine.h>
#include <Graphic/Base Classes/BaseSprite.h>

SimpleMenu::SimpleMenu(GameEngine* engine) : UIMenu::UIMenu(engine)
{
    //BaseSprite* btnOneActiveState = engine->CreateSprite("1", "Menu\\Button_Active.png");
    BaseSprite* btnOneActiveState = engine->CreateSprite("ButtonTest");
    btnOneActiveState->SetZIndex(PRIO::OVERRIDE_TOPMOST);
    btnOneActiveState->SetTextureName("assets\\Menu\\Button_Active.png");
    btnOneActiveState->Show(true);
    
    BaseSprite* btnOneDisabledState = engine->CreateSprite("2", "assets\\Menu\\Button_Disabled.png");
    btnOneDisabledState->SetZIndex(PRIO::UI);

    BaseSprite* btnOneHoverState = engine->CreateSprite("3", "assets\\Menu\\Button_Hover.png");
    btnOneHoverState->SetZIndex(PRIO::UI);

    BaseSprite* btnOnePushedState = engine->CreateSprite("4", "assets\\Menu\\Button_Pushed.png");
    btnOnePushedState->SetZIndex(PRIO::UI);

    BaseSprite* menuBackground = engine->CreateSprite("5", "assets\\Menu\\MenuBackground.png");
    menuBackground->SetZIndex(PRIO::UI);
    menuBackground->Coordinate = DrawObject::GAME_ABSOLUTE;

    ButtonOne = new UIButton(btnOneActiveState, btnOneDisabledState, btnOnePushedState, btnOneHoverState);
    //MenuBackground = menuBackground;

    this->AddElement(ButtonOne);
    
    this->RegisterBackgroundImageAndSetSize(menuBackground);
}

SimpleMenu::~SimpleMenu()
{
    this->RemoveElement(ButtonOne);
    delete(ButtonOne);
}