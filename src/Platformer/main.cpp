#include <GameEngine.h>

#include <GravityObjectsFallDownRule.h>

#include "MarioPlayer.h"

int main()
{
    GameEngine* x = new GameEngine();
    
    // ===== INIT GAME RULES =====
    auto r_grav = new GravityObjectsFallDownRule();
    x->GameRules->Add(r_grav);

    x->Init();

    // ===== INIT GAME SPRITE =====
    BaseSprite* marioSprt = x->CreateSprite("Mario", "mario_01.png"); // Sprite name, sprite texture
    marioSprt->GravityEnabled = true;
    marioSprt->SetScale(4.0);
    //marioSprt->SetPos(50, 50);
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

    // ===== CREATE Z INDEX BLOCK =====
    BaseSprite* qBlock = x->CreateSprite("block", "qmark_block_01.png");
    qBlock->SetScale(4.0);
    qBlock->SpriteFPS = 5;

    SpriteAnimation* qBlockAnim = qBlock->CreateAnimation("idle");
    BaseTexture* qTex01 = x->Graphics->CreateTexture();
    BaseTexture* qTex02 = x->Graphics->CreateTexture();
    BaseTexture* qTex03 = x->Graphics->CreateTexture();
    BaseTexture* qTex04 = x->Graphics->CreateTexture();

    qTex01->Load("qmark_block_01.png");
    qTex02->Load("qmark_block_02.png");
    qTex03->Load("qmark_block_03.png");
    qTex04->Load("qmark_block_04.png");

    qBlockAnim->AnimationFrames->Add(qTex01);
    qBlockAnim->AnimationFrames->Add(qTex02);
    qBlockAnim->AnimationFrames->Add(qTex03);
    qBlockAnim->AnimationFrames->Add(qTex04);

    qBlock->SetPos(50, 400);
    qBlock->Play(true);

    // ===== INIT LOGIC OBJECT =====
    MarioPlayer* player = new MarioPlayer();
    player->engine = x;
    player->sprt = marioSprt;
    player->DropOnGround();

    // ===== START GAMEPLAY =====
    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        x->Play();

        player->Update(); // TODO : Should really be in the GameEngine, requires base classe of LogicObject
    }
    

    return 0;
}