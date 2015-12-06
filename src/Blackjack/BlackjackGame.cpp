#include "BlackjackGame.h"



BlackjackGame::BlackjackGame()
{
    BaseActor::BaseActor();

    GameCards = new CardsShoe();

    BetSelector = new BetSelection();

    Player = new BlackjackPlayer();
    Player->Money = 99999;
    Engine->AttachActor(Player);

    Dealer = new BlackjackDealer();
    Engine->AttachActor(Dealer);
    

    this->Engine->AttachActor(BetSelector);

    SplitCardsDialog = new YesNoDialog("Split ?");
    this->Engine->AttachActor(SplitCardsDialog);

    AskNewCardsDialog = new YesNoDialog("Another card ?");
    this->Engine->AttachActor(AskNewCardsDialog);

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
            this->GameCards->ReSeedDeck();
            this->BetSelector->ResetBet();

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
            while (Player->Cards->Count() < 2)
            {
                Card* playerCard = GameCards->DrawCard();

                Player->ReceiveCard(playerCard);
            }

            while (Dealer->Cards->Count() < 2)
            {
                Card* dealerCard = GameCards->DrawCard();

                Dealer->ReceiveCard(dealerCard);
            }


            bool playerCanSplit = Player->CanSplit();
            bool playerCanInsure = Dealer->BlackjackIsPossible();

            if (playerCanSplit)
            {
                //this->GameState = Game_State::ASK_SPLIT;
                this->GameState = Game_State::PLAYER_NEW_CARDS;
            }
            
            if (playerCanInsure)
            {
                //this->GameState = Game_State::ASK_INSURANCE;
                this->GameState = Game_State::PLAYER_NEW_CARDS;
            }
            
            if (!playerCanSplit && !playerCanInsure)
            {
                this->GameState = Game_State::PLAYER_NEW_CARDS;
            }

            break;
        }
        case ASK_SPLIT:
        {
            if (this->SplitCardsDialog->IsOpen())
            {
                if (this->SplitCardsDialog->DialogDecision != YesNoDialog::DialogResult::CHOOSING)
                {
                    if (this->SplitCardsDialog->DialogDecision != YesNoDialog::DialogResult::YES)
                    {
                        // Split action not implemented
                    }
                    else if (this->SplitCardsDialog->DialogDecision != YesNoDialog::DialogResult::NO)
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
            if (this->AskNewCardsDialog->IsOpen())
            {
                if (this->AskNewCardsDialog->DialogDecision == YesNoDialog::DialogResult::YES)
                {
                    this->AskNewCardsDialog->ResetDialog();

                    Card* newCard = this->GameCards->DrawCard();

                    this->Player->ReceiveCard(newCard);

                    if (this->Player->CardActorCurrentStatus == CardActor::CardPlayerStatus::BUSTED)
                    {
                        // Show busted screen

                        this->GameState = GAME_FINISHED;
                    }
                }
                else if (this->AskNewCardsDialog->DialogDecision == YesNoDialog::DialogResult::NO)
                {
                    this->GameState = DEALER_NEW_CARDS;
                }
            }
            else
            {
                this->AskNewCardsDialog->Open();
            }

            break;
        }

        case GAME_FINISHED:
        {
            ResetGame();
            this->GameState = START;

            break;
        }

        default:
            break;
    }
}

void BlackjackGame::ResetGame()
{
    Player->Cards->Clear();
    Player->Money = 1000;
    Player->LastBet = 0;
    Player->CurrentBet = 0;

    Dealer->Cards->Clear();
    
}
