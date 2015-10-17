#include "InfoTile.h"



InfoTile::InfoTile(int zeroesAmount, int sumAmount, GameEngine* engine)
{
    this->Engine = engine;

    BaseTexture* backgroundTex = engine->Graphics->CreateTexture();
    backgroundTex->Initalize(64, 64);
    backgroundTex->SetSolidColor(0x0000FFFF);

    BackgroundSprite = engine->CreateSprite("InfoTileBackground");

    BackgroundSprite->SetTexture(backgroundTex);

    textFont = engine->Graphics->CreateFont();
    textFont->Load("assets/arial.ttf");

    std::string zeroesAmountString = std::to_string(zeroesAmount);

    nbOfZeroesText = engine->CreateText(zeroesAmountString);
    nbOfZeroesText->SetCharacterSize(72);

    std::string amountString = std::to_string(sumAmount);

    sumOfColumnOrRowText = engine->CreateText(amountString);
    sumOfColumnOrRowText->SetCharacterSize(72);
}


InfoTile::~InfoTile()
{
    delete(textFont);
    delete(nbOfZeroesText);
    delete(sumOfColumnOrRowText);
}
