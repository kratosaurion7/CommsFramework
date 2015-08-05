#pragma once

#include "FSize.h"
#include <string>

struct GraphicEngineInitParams
{
	FSize* WindowSize;
	std::string* WindowTitle;

	bool EnableVerticalSync = true;
};

