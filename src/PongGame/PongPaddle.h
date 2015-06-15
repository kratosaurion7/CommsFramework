#pragma once

#include "Graphical.h"

#include "Macros.h"

enum Directions {
	PADDLE_DIRECTION_LEFT,
	PADDLE_DIRECTION_RIGHT
};

class PongPaddle
{
public:
	PongPaddle(BaseSprite* sprite);
	~PongPaddle();

	BaseSprite* PaddleSprite;

	Vector2<float>* Velocity;

	void Move(Directions direction);

	void SetBounds(int minWidth, int maxWidth);

private:
	int left;
	int right;
};

