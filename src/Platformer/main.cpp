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

    // ===== INIT GAME SPRITE =====
    BaseSprite* marioSprt = x->CreateSprite("Mario", "mario_01.png"); // Sprite name, sprite texture
    marioSprt->GravityEnabled = true;
    marioSprt->SetScale(4.0);
    marioSprt->SetPos(50, 50);
    marioSprt->SpriteFPS = 5;

    // ===== CREATE GROUND =====
    BaseSprite* groundSprt = x->CreateSprite("Ground");
    BaseTexture* groundTex = x->Graphics->CreateTexture();
    groundTex->Initalize(600, 50);
    groundTex->SetSolidColor(0xFA5858FF);

    groundSprt->IsPlaying = true;
    groundSprt->SetTexture(groundTex);
    groundSprt->SetPos(0, 550);

    // ===== CREATE SPRITE ANIMATION =====
    SpriteAnimation* anim = marioSprt->CreateAnimation("walk");
    BaseTexture* tex01 = x->Graphics->CreateTexture();
    BaseTexture* tex02 = x->Graphics->CreateTexture();

    tex01->Load("mario_01.png");
    tex02->Load("mario_02.png");

    anim->AnimationFrames->Add(tex01);
    anim->AnimationFrames->Add(tex02);

    // ===== INIT LOGIC OBJECT =====
    MarioPlayer* player = new MarioPlayer();
    player->engine = x;
    player->sprt = marioSprt;

    // ===== START GAMEPLAY =====
    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        x->Play();

        player->Update();
    }
    

    return 0;
}