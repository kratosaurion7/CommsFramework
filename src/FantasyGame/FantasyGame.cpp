#include "FantasyGame.h"

#include <Engine/GameEngine.h>
#include <Graphic/Base Classes/BaseGraphicEngine.h>
#include <Graphic/Base Classes/BaseSprite.h>
#include <Graphic/Base Classes/BaseTexture.h>

FantasyGame::FantasyGame()
{
    Engine = new GameEngine();
}

FantasyGame::~FantasyGame()
{
    delete(Engine);
}

void FantasyGame::Init()
{
    Engine->Init();

    BaseSprite* test = Engine->CreateSprite();
    BaseTexture* flagTexture = Engine->CreateTexture();
    flagTexture->Load("assets/flag.png");
    test->SetTexture(flagTexture);

    test->Show(true);

    Engine->Graphics->AddObject(test);
}

void FantasyGame::Play()
{
    while(true)
    {
        if(Engine->Keyboard->IsKeyClicked(Key::_Escape))
        {
            break;
        }

        Engine->Play();
    }
}
