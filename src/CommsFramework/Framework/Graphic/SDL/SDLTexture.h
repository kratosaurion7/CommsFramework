#pragma once

class SDLGraphicEngine;

#include <string>
#include <cstdint>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_render.h>

#include "Geometry/FSize.h"

#include "Graphic/Base Classes/BaseTexture.h"

class SDLTexture : public BaseTexture
{
public:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDLGraphicEngine* Graphics;

    int Height;
    int Width;

    SDLTexture();
    ~SDLTexture();

    static SDL_Texture* GetMissingTextureTexture(BaseGraphicEngine* engine);

    virtual void Initalize(float width, float height);

    virtual int Load(std::string path);

    virtual void LoadFromMemory(char* data, int dataSize);

    virtual void LoadFromSurface(SDL_Surface* srcSurface);

    virtual BaseTexture* GetSubTexture(FRectangle rec);

    virtual FSize GetSize();

    virtual void SetSolidColor(uint32_t pixelColor);

    virtual void ResetTextureFromSurface();

    virtual void FreeTexture();

    virtual void SaveTextureToFile();
    virtual void SaveTextureToFile(std::string fileName);

    virtual void OverlayTexture(BaseTexture* other);

private:
    static SDLTexture* MissingTextureSingleton;
    
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const Uint32 rmask = 0xff000000;
    const Uint32 gmask = 0x00ff0000;
    const Uint32 bmask = 0x0000ff00;
    const Uint32 amask = 0x000000ff;
#else
    const Uint32 rmask = 0x000000ff;
    const Uint32 gmask = 0x0000ff00;
    const Uint32 bmask = 0x00ff0000;
    const Uint32 amask = 0xff000000;
#endif

};