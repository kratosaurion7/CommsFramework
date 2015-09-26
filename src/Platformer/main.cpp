#include <GameEngine.h>

#include <GravityObjectsFallDownRule.h>

#include "MarioPlayer.h"

int main()
{
    GameEngine* x = new GameEngine();

    // ===== INIT GAME RULES =====
    auto r_grav = new GravityObjectsFallDownRule();
    x->GameRules->Add(r_grav);

    //x->LoadFromXml("rootConfig.xml");

    x->Init();

    BaseSprite* marioSprt = x->CreateSprite("Mario", "mario_01.png"); // Sprite name, sprite texture
    marioSprt->GravityEnabled = true;
    marioSprt->SetScale(4.0);
    marioSprt->SetPos(50, 50);

    SpriteAnimation* anim = marioSprt->CreateAnimation("walk");
    BaseTexture* tex01 = x->Graphics->CreateTexture();
    BaseTexture* tex02 = x->Graphics->CreateTexture();
    //BaseTexture* tex03 = x->Graphics->CreateTexture();
    //BaseTexture* tex04 = x->Graphics->CreateTexture();
    //BaseTexture* tex05 = x->Graphics->CreateTexture();
    tex01->Load("mario_01.png");
    tex02->Load("mario_02.png");
    //tex03->Load("mario_03.png");
    //tex04->Load("mario_04.png");
    //tex05->Load("mario_05.png");

    anim->AnimationFrames->Add(tex01);
    anim->AnimationFrames->Add(tex02);
    //anim->AnimationFrames->Add(tex03);
    //anim->AnimationFrames->Add(tex04);
    //anim->AnimationFrames->Add(tex05);

    marioSprt->SpriteFPS = 5;
    //marioSprt->Play("walk", true);

    MarioPlayer* player = new MarioPlayer();
    player->engine = x;
    player->sprt = marioSprt;

    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        x->Play();

        player->Update();
    }
    

    return 0;
}