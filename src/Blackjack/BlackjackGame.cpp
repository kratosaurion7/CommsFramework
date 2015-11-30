#include "BlackjackGame.h"



BlackjackGame::BlackjackGame()
{
    BaseActor::BaseActor();

    GameCards = new CardsShoe();

    BetSelector = new BetSelection();

    Player = new BlackjackPlayer();
    Player->Money = 99999;
    Dealer = new BlackjackDealer();

    this->Engine->AttachActor(BetSelector);

    SplitCardsDialog = new SplitCardDialog();

    this->Engine->AttachActor(SplitCardsDialog);

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
                if (this->Player->Money >= this->BetSelector->TotalBet && this->BetSelector->TotalBet > 0)
                {
                    this->Player->CurrentBet = this->BetSelector->TotalBet;

                    this->BetSelector->StopBetSelection();

                    this->GameState = RECEIVE_CARDS;
                }
                else
                {
                    // Insufficient funds. Show error message.
                    this->BetSelector->BettingState = BetSelection::BetSelectState::NEED_SELECTION;
                }
            }
            else if(this->BetSelector->BettingState == BetSelection::BetSelectState::IDLE)
            {
                this->BetSelector->StartBetSelection();
            }

            break;
        }
        case RECEIVE_CARDS:
        {
            while (Player->PlayerCards->Count() <= 2)
            {
                Card* playerCard = GameCards->DrawCard();

                Player->PlayerCards->Add(playerCard);
            }

            while (Dealer->DealerCards->Count() <= 2)
            {
                Card* dealerCard = GameCards->DrawCard();

                Dealer->DealerCards->Add(dealerCard);
            }

            if (Player->CanSplit())
            {
                this->GameState = Game_State::ASK_SPLIT;
            }

            if (Dealer->BlackjackIsPossible())
            {
                this->GameState = Game_State::ASK_INSURANCE;
            }

            break;
        }
        case ASK_SPLIT:
        {
            if (this->SplitCardsDialog->IsOpen())
            {
                if (this->SplitCardsDialog->SplitDecision != SplitCardDialog::DialogResult::CHOOSING)
                {
                    if (this->SplitCardsDialog->SplitDecision != SplitCardDialog::DialogResult::YES)
                    {
                        // Split action not implemented
                    }
                    else if (this->SplitCardsDialog->SplitDecision != SplitCardDialog::DialogResult::NO)
                    {
                        // Split action not implemented
                    }

                    if (Dealer->BlackjackIsPossible())
                    {
                        this->GameState = Game_State::ASK_INSURANCE;
                    }
                    else
                    {
                        this->GameState = Game_State::PLAYER_NEW_CARDS;
                    }
                }
            }
            else
            {
                this->SplitCardsDialog->Open();
            }

            break;
        }
        case ASK_INSURANCE:
        {
            this->GameState = Game_State::PLAYER_NEW_CARDS;

            break;
        }
        case PLAYER_NEW_CARDS:
        {

            break;
        }

        default:
            break;
    }
}
