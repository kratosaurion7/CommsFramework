#pragma once

#include "FSize.h"
#include <string>

class GraphicEngineInitParams
{
public:
	GraphicEngineInitParams();
	~GraphicEngineInitParams();

	FSize* WindowSize;
	std::string* WindowTitle;

	bool EnableVerticalSync = true;
};

