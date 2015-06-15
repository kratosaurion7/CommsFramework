#pragma once

#include "Graphical.h"

class PongBall
{
public:
	PongBall(BaseSprite* sprite);
	~PongBall();

	BaseSprite* BallSprite;

	Vector2<float>* Direction;
	Vector2<float>* Velocity;

	void SetupBounds(int minHeight, int minWidth, int maxHeight, int maxWidth);

	void Update();

	void ResetBallPosition();

private:
	int left;
	int right;
	int top;
	int bottom;
};

