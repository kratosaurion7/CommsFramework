#include "BlackjackDealer.h"



BlackjackDealer::BlackjackDealer()
{
    MoneyLabel->Show(false);
    Money->Show(false);

    LastBetLabel->Show(false);
    LastBet->Show(false);

    CurrentBetLabel->Show(false);
    CurrentBetText->Show(false);

    TotalLabel->Show(false);
    TotalText->Show(false);
}


BlackjackDealer::~BlackjackDealer()
{
}

bool BlackjackDealer::BlackjackIsPossible()
{
    // Let's say the second card is always the one shown to the player
    if (this->Cards->Get(1)->CardValue == Card::CARD_VALUE::Ace)
        return true;

    return false;
}

bool BlackjackDealer::NeedsMoreCards()
{
    // Dealer stops on 17 & up.
    return this->CardsTotal() <= 16; // TODO : Configurable
}

void BlackjackDealer::UpdateCardPositions()
{
    int cardIndex = 0;

    auto it = this->Cards->GetContainer()->begin();
    while (it != this->Cards->GetContainer()->end())
    {
        Card* cardIter = (*it);

        FPosition cardPos;
        cardPos.X = 200 + (100 * cardIndex);
        cardPos.Y = 20;

        cardIter->cardFront->SetPos(cardPos);
        cardIter->cardFront->Show(true);
        cardIter->cardFront->SetZIndex(cardIndex);

        it++;
        cardIndex++;
    }


}
