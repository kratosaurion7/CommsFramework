#include <GameEngine.h>

#include <BaseSprite.h>
#include <BaseTexture.h>
#include <PointerList.h>
#include <Spritesheet.h>

int main()
{
    GameEngine* eng = new GameEngine();

    eng->Init();

    Spritesheet* sp = new Spritesheet("assets//spritesheet.png", eng->Graphics);

    auto sprites = sp->ExtractSprites("assets//spritesheet.xml");

    BaseSprite* first = sprites->First();

    int index = 0;
    auto it = sprites->GetContainer()->begin();
    while (it != sprites->GetContainer()->end())
    {
        BaseSprite* sprt = (*it);

        sprt->GetCurrentTexture()->SaveTextureToFile(std::to_string(index) + ".png");

        index++;

        it++;
    }

    while (true)
    {
        eng->Play();

    }

    return 0;
}