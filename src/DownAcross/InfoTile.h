#pragma once

#include <BaseActor.h>

#include <BaseSprite.h>
#include <BaseTexture.h>
#include <BaseText.h>


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

