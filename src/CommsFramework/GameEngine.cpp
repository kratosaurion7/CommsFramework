#include "GameEngine.h"

#include "GraphicEngine.h"
#include "FSize.h"


GameEngine::GameEngine()
{
	Graphics = new GraphicEngine();
	Resources = new ResourceManager();
}


GameEngine::~GameEngine()
{
	delete(engineInitParams);

	delete(Graphics);

	delete(Resources);
}

void GameEngine::Init(GameEngineInitParams * params)
{
	Graphics->Initialize(params->GraphicsParams);

	Resources->Init(params->RootConfigFile);

	engineInitParams = params;
}


GameEngineInitParams * GameEngineInitParams::CreateDefaultParams()
{
	GameEngineInitParams* newParams = new GameEngineInitParams();
	newParams->RootConfigFile = "config.xml";

	GraphicEngineInitParams* newEngineParams = new GraphicEngineInitParams();
	newEngineParams->EnableVerticalSync = true;
	newEngineParams->WindowSize = new FSize(600, 600);
	newEngineParams->WindowTitle = new std::string("DEFAULT WINDOW TITLE");

	newParams->GraphicsParams = newEngineParams;

	return newParams;
}