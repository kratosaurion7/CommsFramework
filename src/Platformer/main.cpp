#include <GameEngine.h>

int main()
{
    GameEngine* x = new GameEngine();

    //x->LoadFromXml("rootConfig.xml");

    x->Init();

    while (true)
    {
        x->Play();
    }
    

    return 0;
}