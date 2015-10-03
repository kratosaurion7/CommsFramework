#pragma once

#include <BaseSprite.h>
#include <GameEngine.h>
#include <string>

enum MarioPlayerStates
{
    IDLE,
    WALKING,
    JUMPING_START,
    JUMPING
};

enum WalkingDirection
{
    W_LEFT,
    W_RIGHT
};

class MarioPlayer
{
public:
    MarioPlayer();
    ~MarioPlayer();

    GameEngine* engine;

    BaseSprite* sprt;

    MarioPlayerStates CurrentState;
    WalkingDirection MarioDirection;

    void Update();

    void DropOnGround();

private:
    int jumpImpulse = 0;

    void HandleKeyboardInput();

    void HandleCollisions();

    bool HasGroundBelow();

    void SwitchPlayerOrientation(WalkingDirection direction);
};

