#pragma once

#include <BaseActor.h>

class Player;
class FRectangle;

class PlayerCamera : public BaseActor
{
public:
    PlayerCamera(Player* target);
    ~PlayerCamera();

    Player* PlayerToFocus;

    FRectangle* CameraFieldOfView;

    virtual void Update();

};

