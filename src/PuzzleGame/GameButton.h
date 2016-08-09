#pragma once

#define TILE_W 65
#define TILE_H 65

#define TILE_SCALE 1.2

class GameEngine;
class BaseSprite;
class BaseTexture;

#include <BaseActor.h>
#include <PointerList.h>

class GameButton : public BaseActor
{
public:
	BaseSprite* TileSprite;

	BaseTexture* OnTexture;
	BaseTexture* OffTexture;

	bool ButtonIsOn;

	int Index;
	int PosX;
	int PosY;

	GameButton();
	~GameButton();

	void Update();

	void Toggle();
};

extern GameButton*** Arr;
extern PointerList<GameButton*>* list;