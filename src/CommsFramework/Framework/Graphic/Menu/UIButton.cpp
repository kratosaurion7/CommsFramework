#include "UIButton.h"

#include "MouseClickInfo.h"
#include "BaseSprite.h"

UIButton::UIButton(BaseSprite * activeSprite, BaseSprite * disabledSprite, BaseSprite * pushedSprite, BaseSprite * hoverSprite)
{
    this->ActiveButtonSprite = activeSprite;

    if (activeSprite != NULL)
    {
        ElementSprites->Add(activeSprite);
    }

    this->DisabledButtonSprite = disabledSprite;
    this->PushedButtonSprite = pushedSprite;
    this->HoverButtonSprite = hoverSprite;

    IsDisabled = false;
}

UIButton::~UIButton()
{

}

void UIButton::Show()
{
}

void UIButton::Hide()
{
}

void UIButton::Reset()
{
}

void UIButton::Update(MouseClickInfo* mouseInfo)
{
    if (mouseInfo == NULL)
        return;

    switch (CurrentState)
    {
        case UIButton::ACTIVE:
        case UIButton::HOVERED:
            if (this->ActiveButtonSprite->GetRectangle().IsPointInside(mouseInfo->clickPos))
            {
                if (mouseInfo->LeftButtonClicked)
                {
                    CurrentState = UIButtonState::PUSHED;

                    ActiveButtonSprite->Show(false);
                    DisabledButtonSprite->Show(false);
                    PushedButtonSprite->Show(true);
                    HoverButtonSprite->Show(false);
                }
                else
                {
                    CurrentState = UIButtonState::HOVERED;

                    ActiveButtonSprite->Show(false);
                    DisabledButtonSprite->Show(false);
                    PushedButtonSprite->Show(false);
                    HoverButtonSprite->Show(true);
                }
            }
            else
            {
                CurrentState = UIButtonState::ACTIVE;

                ActiveButtonSprite->Show(true);
                DisabledButtonSprite->Show(false);
                PushedButtonSprite->Show(false);
                HoverButtonSprite->Show(false);
            }

            break;
        case UIButton::PUSHED:
            if (this->ActiveButtonSprite->GetRectangle().IsPointInside(mouseInfo->clickPos))
            {
                if (mouseInfo->LeftButtonClicked == false)
                {
                    CurrentState = UIButtonState::CLICKED;

                    Clicked = true;

                    ActiveButtonSprite->Show(true);
                    DisabledButtonSprite->Show(false);
                    PushedButtonSprite->Show(false);
                    HoverButtonSprite->Show(false);
                }
            }
            else
            {
                CurrentState = UIButton::ACTIVE;
            }
            break;
        case UIButton::CLICKED:
            CurrentState = UIButtonState::ACTIVE;
            break;
        case UIButton::DISABLED:

            if (IsDisabled == true)
            {
                ActiveButtonSprite->Show(false);
                DisabledButtonSprite->Show(true);
                PushedButtonSprite->Show(false);
                HoverButtonSprite->Show(false);
            }
            else
            {
                CurrentState = UIButtonState::ACTIVE;

                ActiveButtonSprite->Show(true);
                DisabledButtonSprite->Show(false);
                PushedButtonSprite->Show(false);
                HoverButtonSprite->Show(false);
            }

            break;
        default:
            CurrentState = UIButtonState::ACTIVE;
            break;
    }

    if (CurrentState == UIButtonState::DISABLED)
    {
        ActiveButtonSprite->Show(false);
        DisabledButtonSprite->Show(true);
        PushedButtonSprite->Show(false);
        HoverButtonSprite->Show(false);
    }
    else
    {
        if (this->ActiveButtonSprite->GetRectangle().IsPointInside(mouseInfo->clickPos))
        {
            if (HoverButtonSprite != NULL)
            {
                ActiveButtonSprite->Show(false);
                DisabledButtonSprite->Show(false);
                PushedButtonSprite->Show(false);
                HoverButtonSprite->Show(true);
            }

            if (mouseInfo->LeftButtonClicked)
            {
                ActiveButtonSprite->Show(false);
                DisabledButtonSprite->Show(false);
                PushedButtonSprite->Show(true);
                HoverButtonSprite->Show(false);
            }
        }
        else
        {
            ActiveButtonSprite->Show(true);
            DisabledButtonSprite->Show(false);
            PushedButtonSprite->Show(false);
            HoverButtonSprite->Show(false);
        }
    }
}
