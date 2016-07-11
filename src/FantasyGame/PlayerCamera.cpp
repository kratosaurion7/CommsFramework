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
        this->CameraFieldOfView->Right++;
        this->CameraFieldOfView->Left--;
    }
    if (this->Engine->Keyboard->IsKeyClicked(Key::W))
    {
        this->CameraFieldOfView->Top++;
        this->CameraFieldOfView->Bottom--;
    }
    if (this->Engine->Keyboard->IsKeyClicked(Key::A))
    {
        this->CameraFieldOfView->Left++;
        this->CameraFieldOfView->Right--;
    }
    if (this->Engine->Keyboard->IsKeyClicked(Key::S))
    {
        this->CameraFieldOfView->Bottom++;
        this->CameraFieldOfView->Top--;
    }
}
