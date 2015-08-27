#include "Coin.h"

#include <GameEngine.h>

#include <BaseMouse.h>

Coin::Coin()
{
    this->CurrentState = COIN_IDLE;
}


Coin::~Coin()
{
}

void Coin::Update()
{
    switch (this->CurrentState)
    {
        case COIN_IDLE:
        {
            // Check is coin is clicked
            if (this->CoinSprite->Clicked(LEFT))
            {
                CoinSprite->Show(true);
                this->CurrentState = COIN_START_SPIN;
                animationToStart = "Spin";
            }
            else if (this->CoinSprite->Clicked(RIGHT))
            {
                CoinSprite->Show(true);
                this->CurrentState = COIN_START_SPIN;
                animationToStart = "Bonus";
            }

            break;
        }
        case COIN_START_SPIN:
        {
            CoinSprite->Play(animationToStart, false);

            this->CurrentState = COIN_SPIN;

            break;
        }
        case COIN_SPIN:
        {
            if (!CoinSprite->IsPlaying)
            {
                this->CurrentState = COIN_END_SPIN;
            }

            break;
        }
        case COIN_END_SPIN:
        {
            //CoinSprite->Show(false);
            CoinSprite->Reset();
            CoinSprite->Stop();

            this->CurrentState = COIN_IDLE;
            idleCounter = 0;


            break;
        }
    }

}
