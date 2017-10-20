#pragma once

struct SDL_Texture;

#include <SDL.h>

class SDLDrawable
{
public:
    virtual SDL_Texture* GetDrawableTexture() = 0;
};