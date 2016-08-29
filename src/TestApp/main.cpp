#include <GameEngine.h>
#include <BaseGraphicEngine.h>
#include <BaseSprite.h>
#include <BaseText.h>
#include <BaseTexture.h>



int main()
{
    GameEngine* engine = new GameEngine();
    engine->Init(640, 640);

    BaseGraphicEngine* graphics = engine->Graphics;
    graphics->TextureRepo->LoadTexture("assets\\flag.png");
    

    BaseSprite* sprt = engine->CreateSprite();
    sprt->SetTextureName("flag");
    //sprt->Reload();

    //BaseTexture* tex = graphics->CreateTexture("assets\\img2.png");
    //sprt->SetTexture(tex);

    sprt->SetSize(50, 50);
    sprt->SetPos(25, 25);
    sprt->Show(true);

    while (true)
    {
        engine->Play();
    }


    return 0;
}