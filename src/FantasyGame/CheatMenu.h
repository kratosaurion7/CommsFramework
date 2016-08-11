#pragma once

class BaseSprite;
class BaseTexture;
class BaseText;

#include <BaseActor.h>

class CheatMenu : public BaseActor
{
public:
	CheatMenu();
	~CheatMenu();

	BaseSprite* BackPlate;
	BaseTexture* BackPlateTexture;

	BaseText* SwitchTileNumberLabel;
	BaseText* SwitchTileNumber;

	void Show();
	void Hide();
};

