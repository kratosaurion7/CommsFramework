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
    switch (CurrentState)
    {
        default:
        case IDLE:
            if (engine->Keyboard->IsKeyPressed(Space))
            {
                this->CurrentState = JUMPING_START;
            }

            if (engine->Keyboard->IsKeyPressed(Right))
            {
                this->CurrentState = WALKING;

                MarioDirection = W_RIGHT;

                sprt->Play("walk", true);

            }else if (engine->Keyboard->IsKeyPressed(Left))
            {
                this->CurrentState = WALKING;

                MarioDirection = W_LEFT;

                sprt->Play("walk", true);
            }
            break;
        case WALKING:

            switch (MarioDirection)
            {
                case W_LEFT:
                    sprt->IncrementX(-2);
                    break;
                case W_RIGHT:
                    sprt->IncrementX(2);
                    break;
                default:
                    break;
            }

            if (engine->Keyboard->IsKeyPressed(Left) == false && engine->Keyboard->IsKeyPressed(Right) == false)
            {
                this->CurrentState = IDLE;
                sprt->Stop();
            }

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
