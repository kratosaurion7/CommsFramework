#pragma once

#include "GameEngine.h"
#include "BaseSprite.h"
#include "PointerList.h"

#include "Vectors.h"
#include "FRectangle.h"
#include "FSize.h"

class GameEngine;

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

    PointerList<BaseSprite*>* Sprites;

    void Move(float incrementX, float incrementY);
    void Move(FloatVec incrementVector);

    void MoveTo(float x, float y);
    void MoveTo(FloatVec vec);

    virtual void Update();

    virtual void BindControls(SpriteControls controlScheme = None);

private:
    SpriteControls spriteControlScheme;

    void HandleKeyboardInput();

    void HandleArrows();
    void HandleWASD();

};

