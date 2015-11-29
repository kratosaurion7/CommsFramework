#include "BlackjackGame.h"



BlackjackGame::BlackjackGame()
{
    BaseActor::BaseActor();

    GameCards = new CardsShoe();

    BetSelector = new BetSelection();

    this->Engine->AttachActor(BetSelector);

    this->GameState = START;
}


BlackjackGame::~BlackjackGame()
{
    delete(GameCards);
}

void BlackjackGame::Update()
{
    switch (this->GameState)
    {
        case START:
        {
            // Do game presentation, prompts for options, only the RESET state comes back here

            this->GameState = CHOOSE_BET;

            break;
        }
        case CHOOSE_BET:
        {
            if (this->BetSelector->BettingState == BetSelection::BetSelectState::FINISHED)
            {
                if (this->Player->Money >= this->BetSelector->TotalBet)
                {
                    this->Player->CurrentBet = this->BetSelector->TotalBet;

                    this->BetSelector->StopBetSelection();

                    this->GameState = RECEIVE_CARDS;
                }
                else
                {
                    // Insufficient funds. Show error message.
                }
            }
            else if(this->BetSelector->BettingState == BetSelection::BetSelectState::IDLE)
            {
                this->BetSelector->StartBetSelection();
            }

            break;
        }

        default:
            break;
    }
}
