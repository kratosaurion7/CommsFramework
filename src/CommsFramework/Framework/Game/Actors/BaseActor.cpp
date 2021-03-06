#include "BaseActor.h"

#include "Graphic/Base Classes/BaseGraphicEngine.h"
#include "Engine/GameEngine.h"
#include "Graphic/Base Classes/BaseSprite.h"

#include "Input/Keys.h"

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

void BaseActor::UpdateActor()
{
    this->HandleKeyboardInput();

    this->Update();
}

void BaseActor::Update()
{
    
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

BaseSprite * BaseActor::MakeSprite(std::string name)
{
    BaseSprite* sprt = this->Engine->CreateSprite(name);
    
    this->Sprites->Add(sprt);

    return sprt;
}

BaseText * BaseActor::MakeText(std::string name)
{
    BaseText* txt = this->Engine->CreateText(name);

    this->Sprites->Add(txt);

    return txt;
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
