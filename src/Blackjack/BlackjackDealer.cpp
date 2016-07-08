#include "BlackjackDealer.h"

#include <BaseActor.h>
#include <BaseText.h>
#include <BaseSprite.h>
#include "Card.h"
#include "CardHand.h"

BlackjackDealer::BlackjackDealer()
{
    TotalLabel->Show(false);
    TotalText->Show(false);
}


BlackjackDealer::~BlackjackDealer()
{
}

bool BlackjackDealer::BlackjackIsPossible(int handIndex)
{
    CardHand* hand = this->Hands->Get(handIndex);

    return BlackjackIsPossible(hand);
}

bool BlackjackDealer::BlackjackIsPossible(CardHand * targetHand)
{
    if (targetHand == NULL)
        return false;

    CardHand* hand = targetHand;

    // Let's say the second card is always the one shown to the player
    if (hand->Cards->Get(1)->CardValue == Card::CARD_VALUE::Ace)
        return true;

    return false;
}

bool BlackjackDealer::NeedsMoreCards()
{
    // Dealer stops on 17 & up.
    return this->CardsTotal() <= 16; // TODO : Configurable
}

void BlackjackDealer::Update()
{
    CardActor::Update();

    if (this->CardChoosingState == ASKING_NEW_CARD)
    {
        if (this->NeedsMoreCards())
        {
            this->CardChoosingState = ACCEPTED_CARD;
        }
        else
        {
            this->CardChoosingState = NO_NEW_CARD;
        }
    }
}

void BlackjackDealer::UpdateCardPositions(int handIndex)
{
    CardHand* hand = this->Hands->Get(handIndex);

    UpdateCardPosition(hand);
}

void BlackjackDealer::UpdateCardPosition(CardHand * targetHand)
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
        cardPos.X = 200 + (100 * (float)cardIndex);
        cardPos.Y = 20;

        cardIter->cardFront->SetPos(cardPos);

        cardIter->cardBack->SetPos(cardPos);

        it++;
        cardIndex++;
    }

}
