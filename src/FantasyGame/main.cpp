#include <GameEngine.h>

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init();


    while (true)
    {
        eng->Play();

    }

    return 0;
}