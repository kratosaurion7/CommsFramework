#pragma once

class FPosition
{
public:
    FPosition();
	FPosition(float x, float y);
    ~FPosition();

    float X;

    float Y;

	void Set(float x, float y);
};

