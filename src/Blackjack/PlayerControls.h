#pragma once

class BaseSprite;
class BaseText;

#include <BaseActor.h>

class PlayerControls : public BaseActor
{
public:

    enum PlayerControls_State
    {
        WAITING,
        CHOOSE,
        RECEIVED_INPUT
    };

    PlayerControls();
    ~PlayerControls();

    PlayerControls_State State;

    BaseSprite* DrawButton;
    BaseSprite* HoldButton;

    BaseSprite* SplitButton;
    BaseSprite* DoubleButton;

    void Update();
};

