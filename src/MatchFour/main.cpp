#include <GameEngine.h>
#include <ResourceManager.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>

GameEngine* eng;

BaseGraphicEngine* GameGraphics;

ResourceManager* GameResources;

int main()
{
	GameEngine* eng = new GameEngine();

	GameEngineInitParams* params = GameEngineInitParams::CreateDefaultParams();
	params->ResourceParams->ConfigFileLocation = "match_four_config.xml";

	eng->Init(params);

	eng->Load();

	GameGraphics = eng->Graphics;
	GameResources = eng->Resources;

	BaseSprite* sprt = eng->GetSprite("test");
}