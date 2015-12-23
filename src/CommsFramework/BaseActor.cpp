#include "BaseActor.h"

#include "BaseGraphicEngine.h"
#include "GameEngine.h"
#include "BaseSprite.h"

#include "Keys.h"

BaseActor::BaseActor()
{
    this->Engine = GameEngine::GetInstance();

    Sprites = new PointerList<DrawObject*>();
}

BaseActor::~BaseActor()
{
    delete(Sprites);
}

void BaseActor::Move(float incrementX, float incrementY)
{
    auto it = this->Sprites->GetContainer()->begin();
    while (it != this->Sprites->GetContainer()->end())
    {
        DrawObject* sprt = (*it);

        sprt->IncrementOffsetX(incrementX);
        sprt->IncrementOffsetY(incrementY);

        it++;
    }
}

void BaseActor::Move(FloatVec incrementVector)
{
    this->Move(incrementVector.X, incrementVector.Y);
}

void BaseActor::MoveTo(float x, float y)
{
    auto it = this->Sprites->GetContainer()->begin();
    while (it != this->Sprites->GetContainer()->end())
    {
        DrawObject* sprt = (*it);

        sprt->SetOffsetX(x);
        sprt->SetOffsetY(y);

        it++;
    }
}

void BaseActor::MoveTo(FloatVec vec)
{
    this->MoveTo(vec.X, vec.Y);
}

void BaseActor::Update()
{
    this->HandleKeyboardInput();
}

void BaseActor::BindControls(SpriteControls controlScheme)
{
    this->spriteControlScheme = controlScheme;
}

void BaseActor::WaitFrames(int nbFrames)
{
}

void BaseActor::WaitTime(int millisecondsWait)
{
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
