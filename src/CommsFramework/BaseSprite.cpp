#include "DrawObject.h"

#include "BaseTexture.h"

#include "BaseMouse.h"
#include "FRectangle.h"

#include "BaseGraphicEngine.h"
#include "GameEngine.h"

#include "BaseSprite.h"


bool BaseSprite::MouseOver()
{
    FRectangle myRec = this->GetRectangle();

    Vector2<float> mousePos = GameEngine::Mouse->GetMousePosition();

    return myRec.IsPointInside(mousePos);
}

bool BaseSprite::CollisionWith(BaseSprite * other)
{
    auto myRec = &this->GetRectangle();
    auto otherRec = other->GetRectangle();

    if (otherRec.Intersect(myRec))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BaseSprite::SetTexture(std::string newTexturePath)
{
    //BaseTexture* currentTexture = this->GetCurrentTexture();
    
    //if (currentTexture != NULL)
    //    delete(currentTexture);

    BaseTexture* tex = Engine->CreateTexture(newTexturePath);

    this->SetTexture(tex);
}