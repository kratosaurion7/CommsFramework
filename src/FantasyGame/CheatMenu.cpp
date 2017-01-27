#include "CheatMenu.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <DrawObject.h>
#include <BaseSprite.h>
#include <BaseTexture.h>
#include <BaseText.h>

CheatMenu::CheatMenu()
{
	this->BackPlateTexture = Engine->Graphics->CreateTexture();
	this->BackPlateTexture->Initalize(this->Engine->GameAreaSize->Width, this->Engine->GameAreaSize->Width);
	this->BackPlateTexture->SetSolidColor(0x77000000);

	BackPlate = Engine->CreateSprite();
	BackPlate->SetTexture(BackPlateTexture);
	BackPlate->SetZIndex(990);
	BackPlate->Show(false);
    BackPlate->Coordinate = DrawObject::GAME_ABSOLUTE;

	SwitchTileNumberLabel = this->Engine->CreateText("Switch Tile numbers", 16);
	SwitchTileNumberLabel->SetPos(10, 10);
    SwitchTileNumberLabel->SetZIndex(991);
    SwitchTileNumberLabel->SetStyle(TEXT_STYLE_BOLD);
    SwitchTileNumberLabel->SetColor(0xFFFF0000);
    SwitchTileNumberLabel->Coordinate = DrawObject::GAME_ABSOLUTE;

	SwitchTileNumber = this->Engine->CreateText("1", 16);
	SwitchTileNumber->SetPos(10, 30);
    SwitchTileNumber->SetZIndex(991);
    SwitchTileNumber->SetStyle(TEXT_STYLE_BOLD);
    SwitchTileNumber->SetColor(0xFFFF0000);
    SwitchTileNumber->Coordinate = DrawObject::GAME_ABSOLUTE;
}

CheatMenu::~CheatMenu()
{
	this->Engine->RemoveSprite(BackPlate);
	this->Engine->RemoveText(SwitchTileNumberLabel);
	this->Engine->RemoveText(SwitchTileNumber);

	delete(BackPlate);
	delete(SwitchTileNumberLabel);
	delete(SwitchTileNumber);
}

void CheatMenu::Show()
{
	BackPlate->Show(true);
	SwitchTileNumberLabel->Show(true);
	SwitchTileNumber->Show(true);
}

void CheatMenu::Hide()
{
	BackPlate->Show(false);
	SwitchTileNumberLabel->Show(false);
	SwitchTileNumber->Show(false);
}