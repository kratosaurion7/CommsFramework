#include "InfoTile.h"



InfoTile::InfoTile(int zeroesAmount, int sumAmount, GameEngine* engine)
{
    this->Engine = engine;

    textFont = engine->Graphics->CreateFont();
    textFont->Load("assets/arial.ttf");

    nbOfZeroesText = engine->CreateText("Hello !");
}


InfoTile::~InfoTile()
{
    delete(textFont);
    delete(nbOfZeroesText);
    delete(sumOfColumnOrRowText);
}
