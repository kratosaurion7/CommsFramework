#include "PlayerCamera.h"

#include <FRectangle.h>

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

void PlayerCamera::Update()
{
}
