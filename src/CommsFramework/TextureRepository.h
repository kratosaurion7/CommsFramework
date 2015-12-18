#pragma once

#include <string>

#include "GameEngine.h"
#include "PointerList.h"
#include "BaseTexture.h"

class TextureRepository
{
public:

    TextureRepository(GraphicEngine* engine);
    ~TextureRepository();

    BaseTexture* LoadTexture(std::string texturePath);

private:
    GraphicEngine* Graphics;

    PointerList<BaseTexture*>* loadedTextures;

    BaseTexture* GetLoadedTexture(std::string path);
};

