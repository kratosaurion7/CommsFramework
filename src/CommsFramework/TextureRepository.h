#pragma once

class BaseGraphicEngine;
class BaseTexture;

#include <string>
#include "PointerList.h"

class TextureRepository
{
public:

    TextureRepository(BaseGraphicEngine* engine);
    ~TextureRepository();

    BaseTexture* LoadTexture(std::string texturePath);

private:
    BaseGraphicEngine* Graphics;

    PointerList<BaseTexture*>* loadedTextures;

    BaseTexture* GetLoadedTexture(std::string path);
};

