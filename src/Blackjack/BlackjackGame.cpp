#include "BlackjackGame.h"

#include <YesNoDialog.h>
#include <MessageDialog.h>

#include "Card.h"
#include "CardsShoe.h"
#include "CardActor.h"
#include "BlackjackPlayer.h"
#include "BlackjackDealer.h"
#include "BetSelection.h"
#include <GameEngine.h>
#include "CardActor.h"


BlackjackGame::BlackjackGame()
{
    BaseActor::BaseActor();

    GameCards = new CardsShoe();

    BetSelector = new BetSelection();

    Player = new BlackjackPlayer();
    Player->Money = 100;
    Engine->AttachActor(Player);

    Dealer = new BlackjackDealer();
    Engine->AttachActor(Dealer);
    

    this->Engine->AttachActor(BetSelector);

    SplitCardsDialog = new YesNoDialog("Split ?");
    this->Engine->AttachActor(SplitCardsDialog);

    AskNewCardsDialog = new YesNoDialog("Another card ?");
    this->Engine->AttachActor(AskNewCardsDialog);

    playerWinDialog = new MessageDialog("You win !", 5000);
    this->Engine->AttachActor(playerWinDialog);

    playerLoseDialog = new MessageDialog("You lose.", 3000);
    this->Engine->AttachActor(playerLoseDialog);

    gameDrawDialog = new MessageDialog("Draw.", 4000);
    this->Engine->AttachActor(gameDrawDialog);


    this->GameState = START;
}

BlackjackGame::~BlackjackGame()
{
    delete(GameCards);
}

void BlackjackGame::Update()
{
    BaseActor::Update();

    if (gameDelay > 0)
    {
        gameDelay--;

        return;
    }

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

            Dealer->Cards->Get(0)->TurnDown();

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
                        gameDelay = 60;
                        this->GameState = GAME_FINISHED;
                    }
                }
                else if (this->AskNewCardsDialog->DialogDecision == YesNoDialog::DialogResult::NO)
                {
                    this->AskNewCardsDialog->ResetDialog();

                    this->GameState = DEALER_NEW_CARDS;
                }
            }
            else
            {
                this->AskNewCardsDialog->Open();
            }

            break;
        }
        case DEALER_NEW_CARDS:
        {
            if (this->Dealer->CardChoosingState == CardActor::CardChoosing::IDLE)
            {
                this->Dealer->CardChoosingState = CardActor::CardChoosing::ASKING_NEW_CARD;
            }

            if (this->Dealer->CardChoosingState == CardActor::CardChoosing::ACCEPTED_CARD)
            {
                Card* newCard = this->GameCards->DrawCard();

                this->Dealer->ReceiveCard(newCard);

                this->Dealer->CardChoosingState = CardActor::CardChoosing::ASKING_NEW_CARD;

                gameDelay = 20;
            }

            if(this->Dealer->CardChoosingState == CardActor::CardChoosing::NO_NEW_CARD)
            {
                this->GameState = GAME_FINISHED;
            }

            break;
        }
        case GAME_FINISHED:
        {
            if (this->Player->CardsTotal() > 21)
            {
                this->GameState = DEALER_WINS;
            }
            else if (this->Dealer->CardsTotal() >= 21)
            {
                this->GameState = PLAYER_WINS;
            }
            else
            {
                int playerCloseness = 21 - this->Player->CardsTotal();
                int dealerCloseness = 21 - this->Dealer->CardsTotal();

                if (playerCloseness > dealerCloseness)
                {
                    this->GameState = DEALER_WINS;
                }
                else if (playerCloseness == dealerCloseness)
                {
                    this->GameState = GAME_DRAW;
                }
                else
                {
                    this->GameState = PLAYER_WINS;
                }
            }

            gameDelay = 30;

            break;
        }
        case PLAYER_WINS:
        {
            if (playerWinDialog->DialogState == BaseDialog::DIALOG_CLOSED)
            {
                // Show win celebration
                this->Player->Money += this->Player->CurrentBet * 2;

                playerWinDialog->Open();
            }
            else if (playerWinDialog->DialogState == BaseDialog::DIALOG_DONE)
            {
                this->GameState = RESET;
            }

            break;
        }
        case DEALER_WINS:
        {
            if (playerLoseDialog->DialogState == BaseDialog::DIALOG_CLOSED)
            {
                // Show lose
                this->Player->Money -= this->Player->CurrentBet;

                playerLoseDialog->Open();
            }
            else if (playerLoseDialog->DialogState == BaseDialog::DIALOG_DONE)
            {
                this->GameState = RESET;
            }

            break;
        }
        case GAME_DRAW:
        {
            if (gameDrawDialog->DialogState == BaseDialog::DIALOG_CLOSED)
            {
                gameDrawDialog->Open();
            }
            else if (gameDrawDialog->DialogState == BaseDialog::DIALOG_DONE)
            {
                this->GameState = RESET;
            }

            break;
        }
        case RESET:
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
    GameCards->ReSeedDeck();

    Player->Cards->Clear();
    Dealer->Cards->Clear();

    Player->LastBet = this->Player->CurrentBet;
    Player->CurrentBet = 0;

    Player->CardChoosingState = CardActor::CardChoosing::IDLE;
    Dealer->CardChoosingState = CardActor::CardChoosing::IDLE;

    playerWinDialog->Reset();
    playerLoseDialog->Reset();
    gameDrawDialog->Reset();
}
