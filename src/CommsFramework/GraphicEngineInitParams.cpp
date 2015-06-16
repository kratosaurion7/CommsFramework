#include "GraphicEngineInitParams.h"



GraphicEngineInitParams::GraphicEngineInitParams()
{
}


GraphicEngineInitParams::~GraphicEngineInitParams()
{
	delete WindowSize;
	delete WindowTitle;
}
