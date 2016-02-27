#include "BlackjackGame.h"

#include <YesNoDialog.h>
#include <MessageDialog.h>
#include <GameEngine.h>

#include "Card.h"
#include "CardHand.h"
#include "CardsShoe.h"
#include "CardActor.h"
#include "CardActor.h"
#include "BlackjackPlayer.h"
#include "BlackjackDealer.h"
#include "BetSelection.h"
#include "PlayerControls.h"

BlackjackGame::BlackjackGame()
{
    BaseActor::BaseActor();

    GameCards = new CardsShoe();

    BetSelector = new BetSelection();
    Controls = new PlayerControls();
    Controls->MoveTo(0, 600);
    Controls->Show();

    Player = new BlackjackPlayer();
    Player->Money = 100;
    Engine->AttachActor(Player);

    Dealer = new BlackjackDealer();
    Engine->AttachActor(Dealer);
    

    this->Engine->AttachActor(BetSelector);
    this->Engine->AttachActor(Controls);

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
            this->Controls->Disable();

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
                    this->Player->Money -= this->BetSelector->TotalBet;

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
            CardHand* playerHand = new CardHand();
            Player->Hands->Add(playerHand);

            while (playerHand->Cards->Count() < 2)
            {
                Card* playerCard = GameCards->DrawCard();

                Player->ReceiveCard(playerCard, playerHand);
            }

            CardHand* dealerHand = new CardHand();
            Dealer->Hands->Add(dealerHand);

            while (dealerHand->Cards->Count() < 2)
            {
                Card* dealerCard = GameCards->DrawCard();

                Dealer->ReceiveCard(dealerCard, dealerHand);
            }
            
            dealerHand->Cards->Get(0)->TurnDown();
            dealerHand->Cards->Get(1)->TurnUp();

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
        case ASK_INSURANCE:
        {
            this->GameState = Game_State::PLAYER_NEW_CARDS;

            break;
        }
        case PLAYER_NEW_CARDS:
        {
            if (this->Controls->State == PlayerControls::WAITING)
            {
                this->Controls->Enable(this->Player->CanSplit(), this->Player->Hands->Get(0)->Cards->Count() == 2);
            }
            else if(this->Controls->State == PlayerControls::RECEIVED_INPUT)
            {
                this->Controls->State = PlayerControls::WAIT_INPUT;
                switch (this->Controls->Choice)
                {
                    case PlayerControls::DRAW:
                    {
                        this->Controls->EnableButton(PlayerControls::DOUBLE, false);

                        Card* newCard = this->GameCards->DrawCard();

                        this->Player->ReceiveCard(newCard);

                        if (this->Player->CardActorCurrentStatus == CardActor::CardPlayerStatus::BUSTED)
                        {
                            this->Controls->Disable();
                            // Show busted screen
                            gameDelay = 60;
                            this->GameState = GAME_FINISHED;
                        }

                        break;
                    }
                    case PlayerControls::HOLD:
                    {
                        this->Controls->Disable();
                        this->GameState = DEALER_NEW_CARDS;

                        break;
                    }
                    case PlayerControls::SPLIT:
                    {
                        this->Controls->Disable();
                        break;
                    }
                    case PlayerControls::DOUBLE:
                    {
                        this->Controls->Disable();
                        break;
                    }
                    default:
                        break;
                }
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
            this->Controls->Disable();
            this->Dealer->RevealCards();

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

    Player->Hands->Clear();
    Dealer->Hands->Clear();

    Player->LastBet = this->Player->CurrentBet;
    Player->CurrentBet = 0;

    Player->CardChoosingState = CardActor::CardChoosing::IDLE;
    Dealer->CardChoosingState = CardActor::CardChoosing::IDLE;

    playerWinDialog->Reset();
    playerLoseDialog->Reset();
    gameDrawDialog->Reset();
}
