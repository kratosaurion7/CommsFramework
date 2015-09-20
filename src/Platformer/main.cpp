#include <GameEngine.h>

int main()
{
    GameEngine* x = new GameEngine();

    //x->LoadFromXml("rootConfig.xml");

    x->Init();

    BaseSprite* marioSprt = x->CreateSprite("Mario", "mario_01.png"); // Sprite name, sprite texture
    marioSprt->SetScale(4.0);

    SpriteAnimation* anim = marioSprt->CreateAnimation("walk");
    BaseTexture* tex01 = x->Graphics->CreateTexture();
    BaseTexture* tex02 = x->Graphics->CreateTexture();
    BaseTexture* tex03 = x->Graphics->CreateTexture();
    tex01->Load("mario_01.png");
    tex02->Load("mario_02.png");
    tex03->Load("mario_03.png");

    anim->AnimationFrames->Add(tex01);
    anim->AnimationFrames->Add(tex02);
    anim->AnimationFrames->Add(tex03);

    x->Graphics->AddObject(marioSprt);
    
    marioSprt->SpriteFPS = 5;
    marioSprt->Play("walk", true);

    while (true)
    {
        x->Play();
    }
    

    return 0;
}