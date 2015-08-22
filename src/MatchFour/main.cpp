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
    while (true)
    {
        GameEngine* eng = new GameEngine();

        GameEngineInitParams* params = GameEngineInitParams::CreateDefaultParams();
        params->ResourceParams->ConfigFileLocation = "rootConfig.xml";

        eng->Init(params);

        //eng->Graphics->SetFramerate(15);

        eng->Load();

        GameGraphics = eng->Graphics;
        GameResources = eng->Resources;

        BaseSprite* sprt = eng->GetSprite("Coin");
        sprt->SpriteFPS = 15;

        eng->Graphics->AddObject(sprt);

        eng->Graphics->Start();

        int counter = 0;

        sprt->Play(true);

        while (eng->Graphics->IsRunning())
        {
            eng->Graphics->ProcessEvents();

            sprt->Draw();

            eng->Graphics->Draw();

            //if (counter > 60)
            //{
            //    break;
            //}
            //else {
            //    counter++;
            //}
        }

        delete(eng);
    }
}