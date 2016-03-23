#pragma once

class BaseSprite;
class BaseTexture;
class BaseGraphicEngine;

#include <string>
#include "BaseList.h"
#include "PointerList.h"

class Spritesheet
{
public:
    Spritesheet(std::string spritesheetPath, BaseGraphicEngine* engine);
    ~Spritesheet();

    PointerList<BaseSprite*>* ExtractSprites(std::string configFilePath);

private:
    BaseGraphicEngine* Graphics;

    BaseTexture* spritesheetTexture;
};

