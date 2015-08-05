#include "GameEngine.h"
#include "ResourceManager.h"
#include "BaseGraphicEngine.h"

GameEngine* eng;

BaseGraphicEngine* GameGraphics;

ResourceManager* GameResources;

int main()
{
	GameEngine* eng = new GameEngine();

	eng->Init(GameEngineInitParams::CreateDefaultParams());

	GameGraphics = eng->Graphics;
	GameResources = eng->Resources;

}