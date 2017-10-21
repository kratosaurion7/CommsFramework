#pragma once

class BaseSprite;
class BaseTexture;
class BaseGraphicEngine;

#include <string>
#include "Collections/BaseList.h"
#include "Collections/PointerList.h"

class Spritesheet
{
public:
    Spritesheet(std::string configFilePath, BaseGraphicEngine* engine);
    Spritesheet(std::string spritesheetPath, std::string configFilePath, BaseGraphicEngine* engine);
    ~Spritesheet();

    PointerList<BaseSprite*>* ExtractSprites();

    PointerList<BaseTexture*>* ExtractTextures();

private:
    BaseGraphicEngine* Graphics;

    int spritesheetHeight = 0;
    int spritesheetWidth = 0;

    std::string SpritesheetFilePath;
    std::string ConfigFilePath;

    BaseTexture* spritesheetTexture;
};

