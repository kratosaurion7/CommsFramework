#include <GameEngine.h>

int main()
{
    GameEngine* x = new GameEngine();

    //x->LoadFromXml("rootConfig.xml");

    x->Init();

    BaseSprite* marioSprt = x->CreateSprite("Mario", "sprite.png"); // Sprite name, sprite texture
    marioSprt->SetScale(4.0);

    x->Graphics->AddObject(marioSprt);

    while (true)
    {
        x->Play();
    }
    

    return 0;
}