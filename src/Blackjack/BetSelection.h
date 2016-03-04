#pragma once

class BaseSprite;
class BaseText;

#include <BaseList.h>
#include <PointerList.h>

#include <BaseActor.h>

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
    BaseSprite* ButtonReset;

    BaseList<BetLevels>* BettedLevels;

    BetSelectState BettingState;

    BetSelection();
    ~BetSelection();

    void SetBet(int amount);

    void PlaceBet(BetSelection::BetLevels level);
    void RemoveBet(BetSelection::BetLevels level);
    void ResetBet();

    void StartBetSelection();
    void StopBetSelection();

    void ShowAll();
    void HideAll();

    void Update();

private:
    void UpdateTotalBet();
};

