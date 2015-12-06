#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>

#include "Card.h"

#include "CardActor.h"

class BlackjackDealer : public CardActor
{
public:
    BlackjackDealer();
    ~BlackjackDealer();

    bool BlackjackIsPossible();

protected:
    virtual void UpdateCardPositions();

};

