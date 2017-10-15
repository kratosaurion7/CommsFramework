#include "PlayerControls.h"

#include <GameEngine.h>
#include <BaseSprite.h>
#include <BaseText.h>


PlayerControls::PlayerControls()
{
    //BaseActor::BaseActor();

    State = WAITING;
    Choice = NONE;
    
    DrawButton = this->MakeSprite("DrawButton");
    HoldButton = this->MakeSprite("HoldButton");
    SplitButton = this->MakeSprite("SplitButton");
    DoubleButton = this->MakeSprite("DoubleButton");


    float baseYPos = 25;

    DrawButton->SetTexture("assets//buttons//DrawButton.png");
    DrawButton->SetPos(baseYPos, 0.0);

    HoldButton->SetTexture("assets//buttons//HoldButton.png");
    HoldButton->SetPos(155 * 1 + baseYPos, 0.0);

    SplitButton->SetTexture("assets//buttons//SplitButton.png");
    SplitButton->SetPos(155 * 2 + baseYPos, 0.0);

    DoubleButton->SetTexture("assets//buttons//DoubleButton.png");
    DoubleButton->SetPos(155 *3 + baseYPos, 0.0);
}

PlayerControls::~PlayerControls()
{
}

void PlayerControls::Enable(bool enableSplit, bool enableDouble)
{
    State = WAIT_INPUT;

    DrawButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);
    HoldButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);

    if(enableSplit)
        SplitButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);

    if(enableDouble)
        DoubleButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);
}

void PlayerControls::Disable()
{
    State = WAITING;
    Choice = NONE;

    DrawButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
    HoldButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
    SplitButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
    DoubleButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
}

void PlayerControls::EnableButton(Choice_Result targetButton, bool enable)
{
    if (enable)
    {
        switch (targetButton)
        {
            case PlayerControls::DRAW:
                DrawButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);
                break;
            case PlayerControls::HOLD:
                HoldButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);
                break;
            case PlayerControls::SPLIT:
                SplitButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);
                break;
            case PlayerControls::DOUBLE:
                DoubleButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::NONE);
                break;
            default:
                break;
        }
    }
    else
    {
        switch (targetButton)
        {
            case PlayerControls::DRAW:
                DrawButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
                break;
            case PlayerControls::HOLD:
                HoldButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
                break;
            case PlayerControls::SPLIT:
                SplitButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
                break;
            case PlayerControls::DOUBLE:
                DoubleButton->SetGraphicalFilter(DrawObject::GRAPHIC_FILTER::GRAYSCALE);
                break;
            default:
                break;
        }
    }
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
