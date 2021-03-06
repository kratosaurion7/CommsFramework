#pragma once


class BaseText;
class Card;
class CardHand;

#include <string>

#include <Collections/BaseList.h>
#include <Collections/PointerList.h>

#include <Game/Actors/BaseActor.h>


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

    PointerList<CardHand*>* Hands;

    BaseText* TotalLabel;
    BaseText* TotalText;


    CardActor();
    ~CardActor();

    virtual int CardsTotal(int handIndex = 0);
    virtual int CardsTotal(CardHand* targetHand);
    virtual void ReceiveCard(Card* card, int handIndex = 0);
    virtual void ReceiveCard(Card* card, CardHand* targetHand);
    virtual void Update();

    virtual void RevealCards();
    virtual void HideCards();

    virtual void ClearCards();

protected:
    virtual void UpdateStatusTexts();
    virtual void UpdateCardPositions(int handIndex = 0) = 0;
    virtual void UpdateCardPosition(CardHand* targetHand) = 0;
};