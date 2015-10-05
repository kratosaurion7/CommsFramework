#include <GameEngine.h>

int main()
{
    GameEngine* x = new GameEngine();

    x->Init();

    x->Graphics->SetBackgroundColor(0x00FFFFFF);

    while (true)
    {
        if (x->Keyboard->IsKeyPressed(_Escape))
            break;

        x->Play();
    }


    return 0;
}