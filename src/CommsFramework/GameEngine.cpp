#include "GameEngine.h"

#include "GraphicEngine.h"
#include "FSize.h"

#include "Resource.h"

#include "PointerList.h"

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
	engineInitParams = params;

	Graphics->Initialize(params->GraphicsParams);

	Resources->Init(params->ResourceParams);


}

BaseSprite * GameEngine::GetSprite(std::string name)
{
	BaseSprite* spriteObject = Graphics->CreateSprite();
	
    
    
    PointerList<Resource*>* spriteResource = Resources->GetSpriteResources(name);


	return spriteObject;
}

void GameEngine::Load()
{
	CreateSpritesFromConfig();
}

void GameEngine::CreateSpritesFromConfig()
{

}

GameEngineInitParams * GameEngineInitParams::CreateDefaultParams()
{
	GameEngineInitParams* newParams = new GameEngineInitParams();
	
	ResourceManagerInitParams* newResourceParams = new ResourceManagerInitParams();
	newResourceParams->AssetRootFolder = "Assets\\";
	newResourceParams->ConfigFileLocation = "config.xml";
	newParams->ResourceParams = newResourceParams;

	GraphicEngineInitParams* newEngineParams = new GraphicEngineInitParams();
	newEngineParams->EnableVerticalSync = true;
	newEngineParams->WindowSize = new FSize(600, 600);
	newEngineParams->WindowTitle = new std::string("DEFAULT WINDOW TITLE");
	newParams->GraphicsParams = newEngineParams;

	return newParams;
}