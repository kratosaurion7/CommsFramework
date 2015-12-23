#pragma once


class BaseText;
class Card;

#include <string>

#include <BaseList.h>
#include <PointerList.h>

#include <BaseActor.h>


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