#include <GameEngine.h>

int main()
{
    GameEngine* x = new GameEngine();

    x->Init(1200, 720);

    BaseSprite* blockSprite = x->CreateSprite("Block_01");
    BaseTexture* tex = x->Graphics->CreateTexture();
    tex->Initalize(128, 128);
    tex->SetSolidColor(0xFF0000FF);
    blockSprite->SetTexture(tex);

    x->Graphics->SetBackgroundColor(0x00FFFFFF);

    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        blockSprite->BindControls();

        x->Play();
    }


    return 0;
}