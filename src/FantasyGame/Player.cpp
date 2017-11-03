#include "Player.h"

#include <Engine/GameEngine.h>
#include <Graphic/Base Classes/BaseKeyboard.h>
#include <Graphic/Base Classes/BaseMouse.h>
#include <Graphic/Base Classes/BaseSprite.h>
#include <Graphic/Base Classes/BaseTexture.h>
#include <Graphic/Base Classes/BaseText.h>


Player::Player()
{
    this->PlayerSprite = this->MakeSprite("Player");
    this->PlayerSprite->SetTexture("assets\\flag.png");
    this->PlayerSprite->SetPos(5, 5);
    this->PlayerSprite->SetZIndex(900);
    this->PlayerSprite->Show(true);
}

Player::~Player()
{
}

void Player::Update()
{
    this->Speed = FloatVec(0, 0);

    if (this->Engine->Keyboard->IsKeyPressed(Key::W))
    {
        this->Speed.Y = -5;
    }
    if (this->Engine->Keyboard->IsKeyPressed(Key::S))
    {
        this->Speed.Y = 5;
    }
    if (this->Engine->Keyboard->IsKeyPressed(Key::D))
    {
        this->Speed.X = 5;
    }
    if (this->Engine->Keyboard->IsKeyPressed(Key::A))
    {
        this->Speed.X = -5;
    }

    this->Move(this->Speed);
}
