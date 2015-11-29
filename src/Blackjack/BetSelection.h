#pragma once

#include <BaseList.h>
#include <PointerList.h>
#include <BaseActor.h>

#include <BaseSprite.h>

class BetSelection : public BaseActor
{
public:
    enum BetSelectState
    {
        IDLE,
        NEED_SELECTION,
        FINISHED
    };

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

    int TotalBet;
    BaseText* TotalBetText;

    BaseSprite* ButtonAccept;
    BaseSprite* ButtonCancel;

    BaseList<BetLevels>* BettedLevels;

    BetSelectState BettingState;

    BetSelection();
    ~BetSelection();

    void PlaceBet(BetSelection::BetLevels level);
    void RemoveBet(BetSelection::BetLevels level);

    void StartBetSelection();
    void StopBetSelection();

    void ShowAll();
    void HideAll();

    void Update();

private:
    void UpdateTotalBet();
};

