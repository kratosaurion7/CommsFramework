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

void PongPaddle::SetBounds(int minWidth, int maxWidth)
{
	left = minWidth;
	right = maxWidth;
}

void PongPaddle::Update()
{
	if (Velocity->X > 1)	// Going right
	{
		if (PaddleSprite->GetX() < right - PaddleSprite->GetWidth())
		{
			PaddleSprite->IncrementX(Velocity->X);
		}
	}
	else					// Going left
	{
		if (PaddleSprite->GetX() > 0)
		{
			PaddleSprite->IncrementX(Velocity->X);
		}
	}
}
