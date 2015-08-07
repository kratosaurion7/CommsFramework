#pragma once

#include "GraphicEngine.h"

#include "ResourceManager.h"

#include "BaseSprite.h"

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

	void Load();

	BaseSprite* GetSprite(std::string name);
private:
	GameEngineInitParams* engineInitParams;

	void CreateSpritesFromConfig();

	PointerList<BaseTexture*>* CreateTexturesFromResources(PointerList<Resource*>* resources);
};

