#pragma once

#include "BaseKeyboard.h"



class SFMLKeyboard : public BaseKeyboard
{
public:
	SFMLKeyboard();
	~SFMLKeyboard();

	bool IsKeyPressed(Key key);
};

