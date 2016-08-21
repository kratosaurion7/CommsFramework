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

    BaseSprite* sprt = engine->CreateSprite();
    BaseTexture* tex = graphics->CreateTexture();
    tex->Initalize(128, 128);
    tex->SetSolidColor(0xFF0000FF);

    sprt->SetTexture(tex);
    sprt->SetPos(25, 25);
    sprt->Show(true);

    while (true)
    {
        engine->Play();
    }


    return 0;
}