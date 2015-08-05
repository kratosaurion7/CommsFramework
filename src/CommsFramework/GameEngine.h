#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include <string>

struct GameEngineInitParams
{
	GraphicEngineInitParams* GraphicsParams;

	ResourceManagerInitParams* ResourceParams;

	static GameEngineInitParams* CreateDefaultParams();
};

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	GraphicEngine* Graphics;
	ResourceManager* Resources;

	void Init(GameEngineInitParams* params);

private:
	GameEngineInitParams* engineInitParams;
};

