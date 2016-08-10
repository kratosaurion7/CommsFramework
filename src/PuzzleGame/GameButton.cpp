#include "GameButton.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <BaseSprite.h>
#include <BaseTexture.h>

#include "GameCore.h"

GameButton::GameButton()
{
	ButtonIsOn = false;

	TileSprite = this->MakeSprite("");
	TileSprite->Show(true);
	TileSprite->SetScale(TILE_SCALE);

	OnTexture = this->Engine->Graphics->CreateTexture();
	OnTexture->Initalize(TILE_W, TILE_H);
	OnTexture->SetSolidColor(0xFF0000FF);

	OffTexture = this->Engine->Graphics->CreateTexture();
	OffTexture->Initalize(TILE_W, TILE_H);
	OffTexture->SetSolidColor(0xFF777777);
}


GameButton::~GameButton()
{
}

void GameButton::Update()
{
	if (TileSprite->Clicked())
	{
		ButtonIsOn = !ButtonIsOn;

		if (PosX + 1 < NB_TILES_W)
		{
			Board[PosY][PosX + 1]->Toggle();
		}

		if (PosX - 1 >= 0)
		{
			Board[PosY][PosX - 1]->Toggle();
		}

		if (PosY - 1 >= 0)
		{
			Board[PosY - 1][PosX]->Toggle();
		}

		if (PosY + 1 < NB_TILES_H)
		{
			Board[PosY + 1][PosX]->Toggle();
		}
	}

	if (ButtonIsOn)
	{
		TileSprite->SetTexture(OnTexture);
	}
	else
	{
		TileSprite->SetTexture(OffTexture);
	}
}

void GameButton::Toggle()
{
	ButtonIsOn = !ButtonIsOn;
}
