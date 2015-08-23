#include "BaseSprite.h"

#include "GameEngine.h"

bool BaseSprite::Clicked()
{
    return this->MouseOver() && GameEngine::Mouse->LeftButtonClicked();
}

bool BaseSprite::MouseOver()
{
    FRectangle myRec = this->GetRectangle();

    Vector2<float> mousePos = GameEngine::Mouse->GetMousePosition();

    return myRec.IsPointInside(mousePos);
}
