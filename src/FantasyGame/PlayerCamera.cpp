#include "PlayerCamera.h"

#include <GameEngine.h>
#include <BaseMouse.h>
#include <BaseKeyboard.h>
#include <FRectangle.h>
#include <Vectors.h>

#include "Player.h"

PlayerCamera::PlayerCamera(Player* target)
{
    PlayerToFocus = target;
    CameraFieldOfView = new FRectangle(0, 0, 10, 10);

    CameraSpeed = 4;
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
    if (this->Engine->Keyboard->IsKeyClicked(Key::D))
    {
        this->CameraFieldOfView->Right += CameraSpeed;
        this->CameraFieldOfView->Left -= CameraSpeed;
    }
    if (this->Engine->Keyboard->IsKeyClicked(Key::W))
    {
        this->CameraFieldOfView->Top += CameraSpeed;
            this->CameraFieldOfView->Bottom -= CameraSpeed;
    }
    if (this->Engine->Keyboard->IsKeyClicked(Key::A))
    {
        this->CameraFieldOfView->Left += CameraSpeed;
        this->CameraFieldOfView->Right -= CameraSpeed;
    }
    if (this->Engine->Keyboard->IsKeyClicked(Key::S))
    {
        this->CameraFieldOfView->Bottom += CameraSpeed;
        this->CameraFieldOfView->Top -= CameraSpeed;
    }
}
