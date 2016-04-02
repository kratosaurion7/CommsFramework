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
    Spritesheet(std::string spritesheetPath, std::string configFilePath, BaseGraphicEngine* engine);
    ~Spritesheet();

    PointerList<BaseSprite*>* ExtractSprites();

    PointerList<BaseTexture*>* ExtractTextures();

private:
    BaseGraphicEngine* Graphics;

    std::string SpritesheetFilePath;
    std::string ConfigFilePath;

    BaseTexture* spritesheetTexture;
};

