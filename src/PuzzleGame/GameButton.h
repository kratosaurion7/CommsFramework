#pragma once

class GameEngine;
class BaseSprite;
class BaseTexture;

#include <Game/Actors/BaseActor.h>
#include <Collections/PointerList.h>

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