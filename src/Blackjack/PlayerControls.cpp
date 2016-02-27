#include "PlayerControls.h"

#include <GameEngine.h>
#include <BaseSprite.h>
#include <BaseText.h>


PlayerControls::PlayerControls()
{
    BaseActor::BaseActor();

    State = WAITING;
    Choice = NONE;
    
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

void PlayerControls::Enable()
{
    State = WAIT_INPUT;
}

void PlayerControls::Disable()
{
    State = WAITING;
}

void PlayerControls::Show()
{
    DrawButton->Show(true);
    HoldButton->Show(true);
    SplitButton->Show(true);
    DoubleButton->Show(true);
}

void PlayerControls::Hide()
{
    DrawButton->Show(false);
    HoldButton->Show(false);
    SplitButton->Show(false);
    DoubleButton->Show(false);
}

void PlayerControls::Update()
{
    BaseActor::Update();

    switch (State)
    {
        case PlayerControls::WAITING:
            break;
        case PlayerControls::WAIT_INPUT:
        {
            if (DrawButton->Clicked())
            {
                Choice = DRAW;
                State = RECEIVED_INPUT;
            }
            else if (HoldButton->Clicked())
            {
                Choice = HOLD;
                State = RECEIVED_INPUT;
            }
            else if (SplitButton->Clicked())
            {
                Choice = SPLIT;
                State = RECEIVED_INPUT;
            }
            else if (DoubleButton->Clicked())
            {
                Choice = DOUBLE;
                State = RECEIVED_INPUT;
            }

            break;
        }
        case PlayerControls::RECEIVED_INPUT:
        {
            break;
        }
        default:
            break;
    }
    
}
