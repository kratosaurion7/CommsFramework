#pragma once

template<class T>
class Vector2
{
public:
	Vector2()
	{

	};

	~Vector2()
	{

	};

	T X;
	T Y;

	void Set(T x, T y)
	{
		X = x;
		Y = y;
	};
};