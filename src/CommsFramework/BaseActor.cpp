#include "BaseActor.h"

BaseActor::BaseActor()
{
}

BaseActor::BaseActor(BaseSprite * sprite)
{
}


BaseActor::~BaseActor()
{
}

void BaseActor::Update()
{
    this->Update();
}

void BaseActor::BindControls(SpriteControls controlScheme)
{
    this->spriteControlScheme = controlScheme;
}

void BaseActor::HandleKeyboardInput()
{
    if (this->spriteControlScheme != None)
    {
        switch (this->spriteControlScheme)
        {
            default:
            case Default:
            case Arrows:
            {


                break;
            }
            case WASD:
            {
                break;
            }
        }
    }
}
