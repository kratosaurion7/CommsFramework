#pragma once

#include <string>

#include <BaseList.h>
#include <PointerList.h>

#include <BaseSprite.h>
#include <BaseText.h>
#include <BaseActor.h>

#include "Deck.h"
#include "Card.h"

#include "CardActor.h"

class CardActor : public BaseActor
{
public:
    enum CardChoosing
    {
        IDLE,
        ASKING_NEW_CARD,
        ACCEPTED_CARD,
        NO_NEW_CARD
    } CardChoosingState;

    enum CardPlayerStatus
    {
        OK,
        BUSTED
    } CardActorCurrentStatus;

    PointerList<Card*>* Cards;

    BaseText* MoneyLabel;
    BaseText* Money;

    BaseText* LastBetLabel;
    BaseText* LastBet;

    BaseText* CurrentBetLabel;
    BaseText* CurrentBetText;

    BaseText* TotalLabel;
    BaseText* TotalText;


    CardActor();
    ~CardActor();

    virtual int CardsTotal();
    virtual void ReceiveCard(Card* card);
    virtual void Update();

protected:
    virtual void UpdateStatusTexts();
    virtual void UpdateCardPositions() = 0;
};