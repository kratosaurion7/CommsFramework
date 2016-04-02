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

    BaseTexture* GetTextureByName(std::string textureName);

    PointerList<BaseTexture*>* loadedTextures;
private:
    BaseGraphicEngine* Graphics;

    BaseTexture* GetLoadedTexture(std::string path);
};

