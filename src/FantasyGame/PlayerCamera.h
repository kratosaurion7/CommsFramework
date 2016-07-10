#pragma once

#include <BaseActor.h>

class Player;
class FRectangle;
class FVector;

class PlayerCamera : public BaseActor
{
public:
    PlayerCamera(Player* target);
    ~PlayerCamera();

    Player* PlayerToFocus;

    FRectangle* CameraFieldOfView;

    void SetCameraPosition(FloatVec* newPos);

    virtual void Update();

};

