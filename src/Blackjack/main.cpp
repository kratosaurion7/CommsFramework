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

int main()
{

    GameEngine* eng = new GameEngine();

    eng->Init(800, 800);

    
    eng->Graphics->SetBackgroundColor(101, 156, 239);

    BlackjackGame* game = new BlackjackGame();
    eng->AttachActor(game);

    ////////////////////////// TEST SECTION ///////////////////////
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

    animSprite->SetPos(100, 100);
    animSprite->Play();

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
            SaveTextAsBMP((SDLText*)game->gameDrawDialog->DialogText, "test.bmp");
        }
    }

    return 0;
}