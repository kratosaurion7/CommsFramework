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

    bool doneReduceAces = false;

    while (total > 21 && !doneReduceAces)
    {
        auto it = Cards->GetContainer()->begin();
        while (it != Cards->GetContainer()->end())
        {
            Card* card = (*it);

            if (card->CardValue == Card::Ace && card->CardCountValue != 1)
            {
                card->CardCountValue = 1;

                total -= 10;

                break;
            }

            it++;
        }

        doneReduceAces = true;
    }

    return total;
}
