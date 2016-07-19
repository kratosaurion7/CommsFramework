#pragma once

#include <BaseActor.h>

#include <Vectors.h>

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

    Vector2<int>* CameraSpeed;

    void SetupCamera(FRectangle* fieldOfView, Vector2<int>* scrollSpeed);

    void SetCameraPosition(FloatVec* newPos);

    virtual void Update();
};

