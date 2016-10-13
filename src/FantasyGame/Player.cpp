#include "Player.h"

#include <GameEngine.h>
#include <BaseKeyboard.h>
#include <BaseMouse.h>
#include <BaseSprite.h>
#include <BaseTexture.h>
#include <BaseText.h>


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
