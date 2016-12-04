#include "UIButton.h"

#include "MouseClickInfo.h"
#include "BaseSprite.h"

UIButton::UIButton(BaseSprite * activeSprite, BaseSprite * disabledSprite, BaseSprite * pushedSprite, BaseSprite * hoverSprite)
{
    this->ActiveButtonSprite = activeSprite;
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

void UIButton::Update(MouseClickInfo* mouseInfo)
{
    if (IsDisabled)
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
