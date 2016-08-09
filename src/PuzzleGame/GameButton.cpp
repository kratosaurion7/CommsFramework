#include "GameButton.h"

#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <BaseSprite.h>
#include <BaseTexture.h>

GameButton*** Arr;
PointerList<GameButton*>* list;

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

		GameButton* btn = list->Get(Index + 1);
		if (btn != NULL)
		{
			btn->Toggle();
		}

		btn = list->Get(Index - 1);
		if (btn != NULL)
		{
			btn->Toggle();
		}

		btn = list->Get(Index + 5);
		if (btn != NULL)
		{
			btn->Toggle();
		}
		
		btn = list->Get(Index - 5);
		if (btn != NULL)
		{
			btn->Toggle();
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
