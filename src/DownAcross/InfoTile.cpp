#include "InfoTile.h"



InfoTile::InfoTile(int zeroesAmount, int sumAmount, GameEngine* engine)
{
    this->Engine = engine;

    BaseTexture* backgroundTex = engine->Graphics->CreateTexture();
    backgroundTex->Initalize(128, 128);
    backgroundTex->SetSolidColor(0x0000FFFF);

    BackgroundSprite = engine->CreateSprite("InfoTileBackground");

    BackgroundSprite->SetTexture(backgroundTex);

    textFont = engine->Graphics->CreateFont();
    textFont->Load("assets/arial.ttf");

    nbOfZeroesText = engine->CreateText("Hello !");
    nbOfZeroesText->SetCharacterSize(72);
}


InfoTile::~InfoTile()
{
    delete(textFont);
    delete(nbOfZeroesText);
    delete(sumOfColumnOrRowText);
}
