#pragma once

#include "Graphical.h"

#include "Macros.h"

class PongPaddle
{
public:
	PongPaddle(BaseSprite* sprite);
	~PongPaddle();

	BaseSprite* PaddleSprite;

	Vector2<float>* Velocity;

	void SetBounds(int minWidth, int maxWidth);

	void Update();

private:
	int left;
	int right;
};

