#pragma once

class GameEngine;
class BaseFont;
class BaseText;
class BaseSprite;

#include <BaseActor.h>

class InfoTile : public BaseActor
{
public:
    InfoTile(int zeroesAmount, int sumAmount, GameEngine* engine);
    ~InfoTile();

    int nbOfZeroes = 0;
    int sumOfColumnOrRow = 0;

    BaseFont* textFont;
    BaseText* nbOfZeroesText;
    BaseText* sumOfColumnOrRowText;

    BaseSprite* BackgroundSprite;
};

