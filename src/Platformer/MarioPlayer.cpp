#include "MarioPlayer.h"

#include <BaseKeyboard.h>
#include <Keys.h>

#include <cstdlib>

MarioPlayer::MarioPlayer()
{
}

MarioPlayer::~MarioPlayer()
{
}

void MarioPlayer::Update()
{
    HandleKeyboardInput();

    HandleCollisions();

    switch (CurrentState)
    {
        default:
        case IDLE:
            break;
        case WALKING:
            break;
        case JUMPING_START:
            sprt->Play("jump", false);

            sprt->GravityEnabled = false;

            this->CurrentState = JUMPING;

            break;
        case JUMPING:

            /*if (engine->Keyboard->IsKeyPressed(Space) == false)
            {
                sprt->GravityEnabled = true;
                this->CurrentState = IDLE;
                sprt->Stop();
            }*/

            if (this->jumpImpulse > 0)
            {
                sprt->IncrementY(-20);

                jumpImpulse -= 20;
            }
            else
            {
                this->sprt->GravityEnabled = true;

                if (HasGroundBelow())
                {
                    this->CurrentState = IDLE;
                    
                    break;
                }

            }

            

            break;
    }
}

void MarioPlayer::DropOnGround()
{
    auto it = engine->GameSprites->GetContainer()->begin();
    while (it != engine->GameSprites->GetContainer()->end())
    {
        BaseSprite* other = (*it);

        if (other->Ident.compare("Ground") == 0)
        {
            this->sprt->SetY(sprt->GetY() - this->sprt->GetHeight());
        }

        it++;
    }
}

void MarioPlayer::HandleKeyboardInput()
{
    if (engine->Keyboard->IsKeyPressed(Space))
    {
        if (HasGroundBelow())
        {
            this->jumpImpulse = 200;

            this->sprt->GravityEnabled = false;
            this->CurrentState = JUMPING;
        }
    }
    if (engine->Keyboard->IsKeyPressed(Right))
    {
        sprt->IncrementX(5);

        if (MarioDirection == W_LEFT)
            SwitchPlayerOrientation(W_RIGHT);

        MarioDirection = W_RIGHT;

        if (!sprt->IsPlaying)
        {
            sprt->Play("walk", true);
        }
    }
    if (engine->Keyboard->IsKeyPressed(Left))
    {
        sprt->IncrementX(-5);

        if (MarioDirection == W_RIGHT)
            SwitchPlayerOrientation(W_LEFT);

        MarioDirection = W_LEFT;

        if (!sprt->IsPlaying)
        {
            sprt->Play("walk", true);
        }
    }
    if (engine->Keyboard->IsKeyPressed(Left) == false && engine->Keyboard->IsKeyPressed(Right) == false)
    {
        sprt->Stop();
    }
}

void MarioPlayer::HandleCollisions()
{
    //auto it = engine->GameSprites->GetContainer()->begin();
    //while (it != engine->GameSprites->GetContainer()->end())
    //{
    //    BaseSprite* sprt = (*it);

    //    if (this->sprt->CollisionWith(sprt))
    //    {

    //    }

    //}
}

bool MarioPlayer::HasGroundBelow()
{
    auto it = engine->GameSprites->GetContainer()->begin();
    while (it != engine->GameSprites->GetContainer()->end())
    {
        BaseSprite* other = (*it);

        FRectangle otherRec = other->GetRectangle();

        if (this->sprt != other)
        {
            if (sprt->GetRectangle().Intersect(&otherRec, FRectangle::BottomEdge))
            {
                return true;
            }
        }
        

        it++;
    }

    return false;
}

void MarioPlayer::SwitchPlayerOrientation(WalkingDirection direction)
{
    FloatVec orientationScaleVector = sprt->GetScale();

    switch (direction)
    {
        case W_LEFT:
            orientationScaleVector.X = std::abs(sprt->GetScale().X) * -1;
            break;
        case W_RIGHT:
        default:
            orientationScaleVector.X = std::abs(sprt->GetScale().X);
            break;
    }

    sprt->SetScale(orientationScaleVector);
}
