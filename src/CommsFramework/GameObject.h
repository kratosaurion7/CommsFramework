#pragma once

#include <string>

#include "BaseSprite.h"
#include "GameEngine.h"
#include "PointerList.h"

class GameEngine;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    GameEngine* Engine;

    std::string Identifier;
    
    PointerList<BaseSprite*>* ObjectSprites;

    void Update();
};