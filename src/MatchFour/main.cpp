#include <GameEngine.h>
#include <ResourceManager.h>
#include <BaseGraphicEngine.h>

#include <BaseSprite.h>

#include <FileSystem.h>

GameEngine* eng;

BaseGraphicEngine* GameGraphics;

ResourceManager* GameResources;

#include <Windows.h>

int main()
{
    File* x = new File();

	//while (true)
	//{
		PackageFile* pack = new PackageFile();
		//pack->AddFile("assets\\raven_idle_0.png");
		//pack->AddFile("assets\\raven_idle_1.png");
		//pack->AddFile("assets\\raven_idle_2.png");
		//pack->AddFile("assets\\raven_idle_3.png");
		//pack->AddFile("assets\\raven_idle_4.png");

		for (int i = 0; i < 40; i++)
		{
			pack->AddFile("assets\\win_" + std::to_string(i) + ".png");
		}

		pack->Save("package.pack");


		GameEngine* eng = new GameEngine();

		GameEngineInitParams* params = GameEngineInitParams::CreateDefaultParams();
		params->ResourceParams->ConfigFileLocation = "match_four_config.xml";

		eng->Init(params);

		eng->Load();

		GameGraphics = eng->Graphics;
		GameResources = eng->Resources;

		BaseSprite* sprt = eng->GetSprite("Coin");

		eng->Graphics->AddObject(sprt);

		eng->Graphics->Start();

		int counter = 0;

		while (eng->Graphics->IsRunning())
		{
			eng->Graphics->ProcessEvents();

			sprt->NextFrame();

			eng->Graphics->Draw();

			//if (counter > 60)
			//{
			//	break;
			//}
			//else {
			//	counter++;
			//}
		}

		delete(pack);
		delete(eng);
	//}

}