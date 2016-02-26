#include "PlayerControls.h"

#include <GameEngine.h>
#include <BaseSprite.h>
#include <BaseText.h>


PlayerControls::PlayerControls()
{
    BaseActor::BaseActor();

    State = WAITING;
    
    DrawButton = this->MakeSprite("DrawButton");
    HoldButton = this->MakeSprite("HoldButton");
    SplitButton = this->MakeSprite("SplitButton");
    DoubleButton = this->MakeSprite("DoubleButton");

    DrawButton->SetTexture("assets//buttons//DrawButton.png");
    HoldButton->SetTexture("assets//buttons//HoldButton.png");
    SplitButton->SetTexture("assets//buttons//SplitButton.png");
    DoubleButton->SetTexture("assets//buttons//DoubleButton.png");
}

PlayerControls::~PlayerControls()
{
}

void PlayerControls::Update()
{
    BaseActor::Update();
}
