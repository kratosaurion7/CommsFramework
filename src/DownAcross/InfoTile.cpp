#include "InfoTile.h"

InfoTile::InfoTile(int zeroesAmount, int sumAmount, GameEngine* engine)
{
    this->Engine = engine;

    BaseTexture* backgroundTex = engine->Graphics->CreateTexture();
    backgroundTex->Initalize(64, 64);
    backgroundTex->SetSolidColor(0x95ed64FF);

    BackgroundSprite = engine->CreateSprite("InfoTileBackground");
    BackgroundSprite->SetTexture(backgroundTex);
    this->Sprites->Add(BackgroundSprite);

    textFont = engine->Graphics->CreateFont();
    textFont->Load("assets/arial.ttf");

    std::string zeroesAmountString = std::to_string(zeroesAmount);

    nbOfZeroesText = engine->CreateText(zeroesAmountString);
    nbOfZeroesText->SetCharacterSize(18);
    this->Sprites->Add(nbOfZeroesText);

    std::string amountString = std::to_string(sumAmount);

    sumOfColumnOrRowText = engine->CreateText(amountString);
    sumOfColumnOrRowText->SetCharacterSize(18);
    sumOfColumnOrRowText->SetY(20);
    this->Sprites->Add(sumOfColumnOrRowText);
}


InfoTile::~InfoTile()
{
    delete(textFont);
    delete(nbOfZeroesText);
    delete(sumOfColumnOrRowText);
}
