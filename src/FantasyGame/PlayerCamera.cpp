#include "PlayerCamera.h"

#include <FRectangle.h>
#include <Vectors.h>

#include "Player.h"

PlayerCamera::PlayerCamera(Player* target)
{
    PlayerToFocus = target;
    CameraFieldOfView = new FRectangle(0, 0, 10, 10);
}


PlayerCamera::~PlayerCamera()
{
    delete(CameraFieldOfView);
}

void PlayerCamera::SetCameraPosition(FloatVec* newPos)
{
    this->CameraFieldOfView->Left = newPos->X;
    this->CameraFieldOfView->Top = newPos->Y;
}

void PlayerCamera::Update()
{
}
