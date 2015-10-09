#include <GameEngine.h>

#include <BaseActor.h>

int main()
{
    GameEngine* x = new GameEngine();

    x->Init(1200, 720);

    x->Graphics->SetBackgroundColor(0x00FFFFFF);


    BaseSprite* blockSprite = x->CreateSprite("Block_01");
    BaseTexture* tex = x->Graphics->CreateTexture();
    tex->Initalize(128, 128);
    tex->SetSolidColor(0xFF0000FF);
    blockSprite->SetTexture(tex);

    BaseActor* act = x->CreateActor(blockSprite);
    act->BindControls();

    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        x->Play();
    }


    return 0;
}