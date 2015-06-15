#include "PongPaddle.h"



PongPaddle::PongPaddle(BaseSprite* sprite)
{
	PaddleSprite = sprite;
	Velocity = new Vector2<float>();
	Velocity->Set(0, 0);
}

PongPaddle::~PongPaddle()
{
	SAFE_DELETE(PaddleSprite);
}

void PongPaddle::Move(Directions direction)
{
	if (direction == PADDLE_DIRECTION_LEFT && PaddleSprite->GetX() > 0)
	{
		PaddleSprite->IncrementX(Velocity->X * - 1);
	}
	else if (direction == PADDLE_DIRECTION_RIGHT && right - PaddleSprite->GetWidth())
	{
		PaddleSprite->IncrementX(Velocity->X);
	}
}

void PongPaddle::SetBounds(int minWidth, int maxWidth)
{
	left = minWidth;
	right = maxWidth;
}