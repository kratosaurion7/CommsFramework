#include "PlayerCamera.h"

#include <GameEngine.h>
#include <BaseMouse.h>
#include <BaseKeyboard.h>
#include <BaseSprite.h>
#include <FRectangle.h>
#include <Vectors.h>
#include <SettingsRepository.h>

#include "Player.h"

PlayerCamera::PlayerCamera(Player* target)
{
    PlayerToFocus = target;
    CameraFieldOfView = new FRectangle(0, 0, 10, 10);

    CameraSpeed = new Vector2<int>(4, 4);
}


PlayerCamera::~PlayerCamera()
{
    delete(CameraFieldOfView);
}

void PlayerCamera::SetupCamera(FRectangle* fieldOfView, Vector2<int>* scrollSpeed)
{
    if (this->CameraFieldOfView != NULL)
    {
        delete(CameraFieldOfView);
    }

    CameraFieldOfView = fieldOfView;

    if (this->CameraSpeed != NULL)
    {
        delete(CameraSpeed);
    }

    this->CameraSpeed = scrollSpeed;
}

void PlayerCamera::SetCameraPosition(FloatVec* newPos)
{
    this->CameraFieldOfView->Left = newPos->X;
    this->CameraFieldOfView->Top = newPos->Y;
}

void PlayerCamera::Update()
{
    float cameraX = this->PlayerToFocus->PlayerSprite->GetOffsetPos().X - (this->CameraFieldOfView->Width() / 2);
    float cameraY = this->PlayerToFocus->PlayerSprite->GetOffsetPos().Y - (this->CameraFieldOfView->Height() / 2);

    this->CameraFieldOfView->Set(cameraX, cameraY);
}