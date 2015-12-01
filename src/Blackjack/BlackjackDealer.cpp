#include "BlackjackDealer.h"



BlackjackDealer::BlackjackDealer()
{
    DealerCards = new PointerList<Card*>();
}


BlackjackDealer::~BlackjackDealer()
{
}

int BlackjackDealer::CardsTotal()
{
    int totalValue = 0;

    auto it = DealerCards->GetContainer()->begin();
    while (it != DealerCards->GetContainer()->end())
    {
        Card* card = (*it);

        totalValue += card->CardValue;

        it++;
    }

    return totalValue;
}

bool BlackjackDealer::BlackjackIsPossible()
{
    // Let's say the first card is always the one shown to the player
    if (this->DealerCards->Get(0)->CardValue == Card::CARD_VALUE::Ace)
        return true;

    return false;
}

void BlackjackDealer::ReceiveCard(Card * card)
{
    this->DealerCards->Add(card);
}
