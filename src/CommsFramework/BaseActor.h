#pragma once

#include "GameEngine.h"
#include "BaseSprite.h"
#include "PointerList.h"

enum SpriteControls
{
    None,
    Default,
    Arrows,
    WASD
};

class BaseActor
{
public:
    BaseActor();
    BaseActor(BaseSprite* sprite);
    ~BaseActor();

    GameEngine* Engine;

    PointerList<BaseSprite*> Sprites;

    void Update();

    void BindControls(SpriteControls controlScheme = None);

private:
    SpriteControls spriteControlScheme;

};

