#include "BlackjackPlayer.h"

#include <BaseActor.h>
#include <BaseText.h>
#include <BaseSprite.h>
#include <GameEngine.h>

#include "Card.h"
#include "CardHand.h"


BlackjackPlayer::BlackjackPlayer()
{
    this->CurrentBet = 0;
    this->LastBet = 0;
    this->Money = 0;

    MoneyText = Engine->CreateText("0");
    MoneyText->SetPos(0, 700);

    MoneyLabel = Engine->CreateText(" Money");
    MoneyLabel->SetPos(0, 680);
    MoneyLabel->SetColor(0xFFFFFFFF);
    MoneyLabel->SetCharacterSize(16);

    MoneyLabel->Show(true);
    MoneyText->Show(true);


    LastBetLabel = Engine->CreateText("Last bet");
    LastBetLabel->SetPos(150, 680);
    LastBetLabel->SetColor(0xFFFFFFFF);
    LastBetLabel->SetCharacterSize(16);


    LastBetText = Engine->CreateText("0");
    LastBetText->SetPos(150, 700);
    LastBetText->Show(true);
    LastBetLabel->Show(true);


    CurrentBetLabel = Engine->CreateText("Current Bet");
    CurrentBetLabel->SetPos(300, 680);
    CurrentBetLabel->SetColor(0xFFFFFFFF);
    CurrentBetLabel->SetCharacterSize(16);

    CurrentBetText = Engine->CreateText("0");
    CurrentBetText->SetPos(300, 700);
    CurrentBetLabel->Show(true);
    CurrentBetText->Show(true);
}


BlackjackPlayer::~BlackjackPlayer()
{
}

bool BlackjackPlayer::CanSplit(int handIndex)
{
    CardHand* hand = this->Hands->Get(handIndex);

    return this->CanSplit(hand);
}

bool BlackjackPlayer::CanSplit(CardHand * targetHand)
{
    if (targetHand == NULL)
        return false;

    CardHand* hand = targetHand;

    // Confirm if can split when card 0 = 10 and card 1 = Jack/Queen/King
    if (hand->Cards->Get(0)->CardValue == hand->Cards->Get(1)->CardValue)
        return true;

    return false;
}

void BlackjackPlayer::UpdateCardPositions(int handIndex)
{
    CardHand* hand = this->Hands->Get(handIndex);

    UpdateCardPosition(hand);
}

void BlackjackPlayer::UpdateCardPosition(CardHand* targetHand)
{
    if (targetHand == NULL)
        return;

    CardHand* hand = targetHand;

    int cardIndex = 0;

    auto it = hand->Cards->GetContainer()->begin();
    while (it != hand->Cards->GetContainer()->end())
    {
        Card* cardIter = (*it);

        FPosition cardPos;
        cardPos.X = 200 + (100 * cardIndex);
        cardPos.Y = 400;

        cardIter->cardFront->SetPos(cardPos);
        cardIter->cardFront->Show(true);
        //cardIter->cardFront->SetZIndex(cardIndex);

        cardIter->cardBack->SetPos(cardPos);
        cardIter->cardBack->Show(false);
        //cardIter->cardBack->SetZIndex(cardIndex);

        it++;
        cardIndex++;
    }
}

void BlackjackPlayer::UpdateStatusTexts()
{
    CardActor::UpdateStatusTexts();

    std::string money = std::to_string(this->Money);
    this->MoneyText->SetText(money);

    std::string currentBet = std::to_string(this->CurrentBet);
    this->CurrentBetText->SetText(currentBet);

    std::string lastBet = std::to_string(this->LastBet);
    this->LastBetText->SetText(lastBet);
}
