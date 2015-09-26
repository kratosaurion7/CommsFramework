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
                this->CurrentState = JUMPING;
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
        case JUMPING:

            sprt->IncrementY(1);

            sprt->Play("jump", false);

            //if (engine->Keyboard->IsKeyPressed(Space) == false)
            //{
            //    this->CurrentState = IDLE;
            //}

            break;
    }
}
