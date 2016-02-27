#pragma once

class DrawObject;
class BaseSprite;
class BaseText;

#include <BaseActor.h>
#include <PointerList.h>

class PlayerControls : public BaseActor
{
public:

    enum PlayerControls_State
    {
        WAITING,
        WAIT_INPUT,
        RECEIVED_INPUT
    };

    enum Choice_Result
    {
        NONE,

        DRAW,
        HOLD,
        SPLIT,
        DOUBLE
    };

    PlayerControls();
    ~PlayerControls();

    void Enable();
    void Disable();

    void Show();
    void Hide();

    PlayerControls_State State;

    Choice_Result Choice;

    BaseSprite* DrawButton;
    BaseSprite* HoldButton;

    BaseSprite* SplitButton;
    BaseSprite* DoubleButton;

    void Update();

private:
    bool enabled;

};

