#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>

#include <BaseSprite.h>

class BetSelection : public BaseActor
{
public:
    enum BetLevels
    {
        One = 1,
        Five = 5,
        Ten = 10,
        TwentyFive = 25,
        OneHundred = 100
    };

    BaseSprite* BetOne;
    BaseSprite* BetFive;
    BaseSprite* BetTen;
    BaseSprite* BetTwentyFive;
    BaseSprite* BetOneHundred;

    BaseText* TotalBet;

    BaseSprite* ButtonAccept;
    BaseSprite* ButtonCancel;

    BaseList<BetLevels>* BettedLevels;

    BetSelection();
    ~BetSelection();

    void PlaceBet(BetSelection::BetLevels level);
    void RemoveBet(BetSelection::BetLevels level);

    void ShowBetSelection();
    void HideBetSelection();

    void ShowAll();
    void HideAll();

private:
    void UpdateTotalBet();
};

