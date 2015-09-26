#include "MarioPlayer.h"

#include <BaseKeyboard.h>
#include <Keys.h>

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

            if (engine->Keyboard->IsKeyPressed(Space) == false)
            {
                sprt->GravityEnabled = true;
                this->CurrentState = IDLE;
                sprt->Stop();
            }

            sprt->IncrementY(-3);

            break;
    }
}

void MarioPlayer::DropOnGround()
{
    auto it = engine->GameSprites->GetContainer()->begin();
    while (it != engine->GameSprites->GetContainer()->end())
    {
        BaseSprite* sprt = (*it);

        if (sprt->Ident.compare("Ground") == 0)
        {
            this->sprt->SetY(sprt->GetY() - this->sprt->GetHeight());
        }

        it++;
    }
}

void MarioPlayer::HandleKeyboardInput()
{
    if (engine->Keyboard->IsKeyPressed(Space) && this->CurrentState != JUMPING)
    {
        this->CurrentState = JUMPING_START;
    }
    if (engine->Keyboard->IsKeyPressed(Right))
    {
        sprt->IncrementX(2);

        MarioDirection = W_RIGHT;

        if (!sprt->IsPlaying)
        {
            sprt->Play("walk", true);
        }
    }
    if (engine->Keyboard->IsKeyPressed(Left))
    {
        sprt->IncrementX(-2);

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
