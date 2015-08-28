#include "BaseSprite.h"

#include "GameEngine.h"

bool BaseSprite::Clicked(MouseButtons targetButton)
{
    if (targetButton == LEFT)
    {
        return this->MouseOver() && GameEngine::Mouse->LeftButtonClicked();
    }
    else if (targetButton == RIGHT)
    {
        return this->MouseOver() && GameEngine::Mouse->RightButtonClicked();
    }
}

bool BaseSprite::MouseOver()
{
    FRectangle myRec = this->GetRectangle();

    Vector2<float> mousePos = GameEngine::Mouse->GetMousePosition();

    return myRec.IsPointInside(mousePos);
}

void BaseSprite::ApplyDescriptor(SpriteDescriptor* descriptor)
{
    this->SetPos(descriptor->Position);
    //this->SetSize(descriptor->Size);
}
