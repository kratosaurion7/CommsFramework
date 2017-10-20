#pragma once

#include "PointerList.h"
#include "Vectors.h"
#include "FRectangle.h"
#include "FSize.h"

class GameEngine;
class DrawObject;
class BaseSprite;
class BaseText;

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
    virtual ~BaseActor();

    GameEngine* Engine;

    PointerList<DrawObject*>* Sprites;

    virtual void Move(float incrementX, float incrementY);
    virtual void Move(FloatVec incrementVector);

    virtual void MoveTo(float x, float y);
    virtual void MoveTo(FloatVec vec);

    // This method is used to make sure that updating an actor always goes through a base
    // method. Useful when trying to implement logic in the BaseActor that affects the base
    // class in a way that cannot be overridden away.
    void UpdateActor();

    virtual void Update();

    virtual void BindControls(SpriteControls controlScheme = None);

    void WaitFrames(int nbFrames);
    void WaitTime(int millisecondsWait);

protected:
    // Utility methods to create and then add sprites automatically
    // TODO : Find better name to illustrate that the actor will keep track of the sprite
    BaseSprite* MakeSprite(std::string name);
    BaseText* MakeText(std::string name);

private:
    SpriteControls spriteControlScheme;

    void HandleKeyboardInput();

    void HandleArrows();
    void HandleWASD();

};

