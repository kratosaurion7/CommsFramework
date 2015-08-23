#include "Coin.h"

#include <GameEngine.h>

Coin::Coin()
{
    this->CurrentState = COIN_IDLE;
}


Coin::~Coin()
{
}

void Coin::Clicked()
{
    if (this->CurrentState == COIN_IDLE)
    {
        this->CurrentState = COIN_START_SPIN;
    }
}

void Coin::Update()
{
    switch (this->CurrentState)
    {
        case COIN_IDLE:
        {
            // Check is coin is clicked
            if (this->CoinSprite->GetRectangle().IsPointInside(GameEngine::Mouse->GetMousePosition()) && GameEngine::Mouse->LeftButtonClicked())
            {
                CoinSprite->Show(true);
                this->CurrentState = COIN_START_SPIN;
            }

            break;
        }
        case COIN_START_SPIN:
        {
            CoinSprite->Play(true);

            this->CurrentState = COIN_SPIN;

            break;
        }
        case COIN_SPIN:
        {
            coinSpinCounter++;

            if (coinSpinCounter >= 300)
            {
                coinSpinCounter = 0;
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
