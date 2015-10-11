#include "BaseActor.h"

BaseActor::BaseActor()
{
    Sprites = new PointerList<BaseSprite*>();
}

BaseActor::BaseActor(BaseSprite * sprite)
{
    Sprites = new PointerList<BaseSprite*>();
    Sprites->Add(sprite);
}


BaseActor::~BaseActor()
{
}

void BaseActor::Move(float incrementX, float incrementY)
{
    auto it = this->Sprites->GetContainer()->begin();
    while (it != this->Sprites->GetContainer()->end())
    {
        BaseSprite* sprt = (*it);

        sprt->IncrementX(incrementX);
        sprt->IncrementY(incrementY);

        it++;
    }
}

void BaseActor::Move(FloatVec incrementVector)
{
    this->Move(incrementVector.X, incrementVector.Y);
}

void BaseActor::Update()
{
    this->HandleKeyboardInput();
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
                this->HandleArrows();

                break;
            }
            case WASD:
            {
                this->HandleWASD();

                break;
            }
        }
    }
}

void BaseActor::HandleArrows()
{
    if (Engine->Keyboard->IsKeyPressed(Left))
    {
        this->Move(-2, 0);
    }
    if (Engine->Keyboard->IsKeyPressed(Right))
    {
        this->Move(2, 0);
    }
    if (Engine->Keyboard->IsKeyPressed(Up))
    {
        this->Move(0, -2);
    }
    if (Engine->Keyboard->IsKeyPressed(Down))
    {
        this->Move(0, 2);
    }
}

void BaseActor::HandleWASD()
{
    if (Engine->Keyboard->IsKeyPressed(A))
    {
        this->Move(-2, 0);
    }
    if (Engine->Keyboard->IsKeyPressed(D))
    {
        this->Move(2, 0);
    }
    if (Engine->Keyboard->IsKeyPressed(W))
    {
        this->Move(0, -2);
    }
    if (Engine->Keyboard->IsKeyPressed(S))
    {
        this->Move(0, 2);
    }

}
