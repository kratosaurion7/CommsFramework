#include "Card.h"

#include <BaseSprite.h>
#include <GameEngine.h>

Card::Card()
{
    this->cardBack = NULL;
    this->cardFront = NULL;

    this->CardSuit = (Card::CARD_SUITS)0;
    this->CardValue = (Card::CARD_VALUE)0;
}


Card::~Card()
{
    if (this->cardBack != NULL)
    {
        this->Engine->RemoveSprite(cardBack);

        delete(cardBack);
    }

    if (this->cardFront != NULL)
    {
        this->Engine->RemoveSprite(cardFront);

        delete(cardFront);
    }

    Engine->DetachActor(this);
}

void Card::TurnUp()
{
    this->cardBack->Show(false);
    this->cardFront->Show(true);
}

void Card::TurnDown()
{
    this->cardBack->Show(true);
    this->cardFront->Show(false);
}

void Card::Update()
{
    BaseActor::Update();
}
