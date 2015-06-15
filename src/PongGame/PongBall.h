#pragma once

#include "Graphical.h"

class PongBall
{
public:
	PongBall(DSprite* sprite);
	~PongBall();

	DSprite* BallSprite;

	Vector2<float>* Direction;
	Vector2<float>* Velocity;

	void SetupBounds(int minHeight, int minWidth, int maxHeight, int maxWidth);

	void Update();

private:
	int left;
	int right;
	int top;
	int bottom;
};

