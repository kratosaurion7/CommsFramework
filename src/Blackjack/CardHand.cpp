#include "CardHand.h"

#include "Card.h"

CardHand::CardHand()
{
    Cards = new PointerList<Card*>();
}


CardHand::~CardHand()
{
    delete(Cards);
}

int CardHand::GetTotal()
{
    int total = 0;

    auto it = Cards->GetContainer()->begin();
    while (it != Cards->GetContainer()->end())
    {
        Card* card = (*it);

        total += card->CardCountValue;

        it++;
    }

    return total;
}
