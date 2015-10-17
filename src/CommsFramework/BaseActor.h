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
    ~BaseActor();

    GameEngine* Engine;

    PointerList<DrawObject*>* Sprites;

    virtual void Move(float incrementX, float incrementY);
    virtual void Move(FloatVec incrementVector);

    virtual void MoveTo(float x, float y);
    virtual void MoveTo(FloatVec vec);

    virtual void Update();

    virtual void BindControls(SpriteControls controlScheme = None);

private:
    SpriteControls spriteControlScheme;

    void HandleKeyboardInput();

    void HandleArrows();
    void HandleWASD();

};

