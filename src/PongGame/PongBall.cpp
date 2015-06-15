#include "PongBall.h"

#include "Macros.h"

PongBall::PongBall(DSprite* sprite)
{
	BallSprite = sprite;
	Direction = new Vector2<float>();
	Velocity = new Vector2<float>();
}

PongBall::~PongBall()
{
	SAFE_DELETE(BallSprite);
	SAFE_DELETE(Direction);
	SAFE_DELETE(Velocity);
}

void PongBall::SetupBounds(int minHeight, int minWidth, int maxHeight, int maxWidth)
{
	top = minHeight;
	left = minWidth;
	bottom = maxHeight;
	right = maxWidth;
}

void PongBall::Update()
{
	if (Velocity->X > 0)	// Going right
	{
		if (BallSprite->GetX() + BallSprite->GetWidth() < right)
		{
			BallSprite->IncrementX(Direction->X * Velocity->X);
		}
	}
	else					// Going left
	{
		if (BallSprite->GetX() > left)
		{
			BallSprite->IncrementX(Direction->X * Velocity->X);
		}
	}

	if (Velocity->Y > 0)	// Going down
	{
		if (BallSprite->GetY() + BallSprite->GetHeight() < bottom)
		{
			BallSprite->IncrementY(Direction->Y * Velocity->Y);
		}
	}
	else					// Going up
	{
		if (BallSprite->GetY() > top)
		{
			BallSprite->IncrementY(Direction->Y * Velocity->Y);
		}
	}
}
