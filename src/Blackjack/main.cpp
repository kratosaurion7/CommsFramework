#include <BaseGraphicEngine.h>
#include <GameEngine.h>
#include <LiteList.h>

#include "Deck.h"
#include "Card.h"

#include "BlackjackGame.h"

#include <MessageDialog.h>
#include <SDLUtilities.h>

#include <StringList.h>
#include <SpriteAnimation.h>
#include <FileSave.h>

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    
    eng->Graphics->SetBackgroundColor(101, 156, 239);

    BlackjackGame* game = new BlackjackGame();
    eng->AttachActor(game);

    ////////////////////////// TEST SECTION ///////////////////////
    char* data = "1234567890";
    std::string message = "Hello World";

    FileSave* newSave = new FileSave();
    newSave->AddBool("one", true);
    newSave->AddBool("two", false);
    newSave->AddData("three", data, strlen(data));
    newSave->AddNumber("four", 999);
    newSave->AddString("five", &message);

    //newSave->SaveToFile("save.bin");

    FileSave* loaded = FileSave::LoadFromFile("save.bin");

    BaseSprite* animSprite = eng->CreateSprite("animu");
    BaseTexture* one = eng->Graphics->CreateTexture("assets\\one.png");
    BaseTexture* two = eng->Graphics->CreateTexture("assets\\two.png");
    BaseTexture* three = eng->Graphics->CreateTexture("assets\\three.png");
    BaseTexture* four = eng->Graphics->CreateTexture("assets\\four.png");

    SpriteAnimation* anim = new SpriteAnimation();
    anim->Frames->Add(one);
    anim->Frames->Add(two);
    anim->Frames->Add(three);
    anim->Frames->Add(four);
    animSprite->AddAnimation(anim);
    animSprite->IsAnimated = true;
    animSprite->Show(true);

    animSprite->SetPos(100, 100);
    animSprite->Play(true);

    //////////////////////// END TEST SECTION /////////////////////


    while (true)
    {
        eng->Play();

        if (eng->Keyboard->IsKeyClicked(Key::_Escape))
        {
            break;
        }

        if (eng->Keyboard->IsKeyClicked(Key::Space))
        {
            eng->Graphics->Scale(0.5);
        }
    }

    return 0;
}