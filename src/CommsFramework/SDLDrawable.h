#pragma once

class SDL_Texture;

#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_render.h>

class SDLDrawable
{
public:
    virtual SDL_Texture* GetDrawableTexture() = 0;
};