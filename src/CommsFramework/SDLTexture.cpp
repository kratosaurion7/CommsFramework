#include "SDLTexture.h"

#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_render.h>

#include "SDLUtilities.h"
#include "SDLGraphicEngine.h"

SDLTexture::SDLTexture()
{
    surface = NULL;
    texture = NULL;
    Graphics = NULL;
}

SDLTexture::~SDLTexture()
{
    if (texture != NULL)
        SDL_DestroyTexture(texture);

    if (surface != NULL)
        SDL_FreeSurface(surface);
}

void SDLTexture::Initalize(float width, float height)
{
    Height = height;
    Width = width;
}

void SDLTexture::Load(std::string path)
{
    // Only BMP images supported for now
    // TODO : Get libpng in here !
    // TODO : Get libjpeg in here !
    
    int res = 0;
    const char* errorString;

    surface = SDL_LoadBMP(path.c_str());

    if (surface == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create surface for [%s] with error %s\n", path.c_str(), errorString);

        return;
    }

    SDL_Renderer* renderer = Graphics->gameRenderer;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create texture for [%s] with error %s\n", path.c_str(), errorString);

        return;
    }

    // TODO : Check if we keep both the Texture and Surface in memory
    // SDL_FreeSurface(surface); // Must keep surface to use GetSubTexture()
    TexturePath = path;
}

void SDLTexture::LoadFromMemory(char* data, int dataSize)
{
}

void SDLTexture::LoadFromSurface(SDL_Surface* surface)
{
    const char* errorString;
    SDL_Renderer* renderer = Graphics->gameRenderer;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create texture from surface with error %s\n", errorString);

        return;
    }

    TexturePath = "";
}

BaseTexture* SDLTexture::GetSubTexture(FRectangle rec)
{
    int res = 0;
    SDLTexture* newTexture;

    FSize* recSize = rec.Size();
    SDL_Rect sRec = FRectToSDL_Rect(rec);
    
    SDL_Surface* subTextureSurface = SDL_CreateRGBSurface(0, recSize->Width, recSize->Height, 32, 0, 0, 0, 0);

    res = SDL_BlitSurface(this->surface, &sRec, subTextureSurface, NULL);

    newTexture = new SDLTexture();
    newTexture->LoadFromSurface(subTextureSurface);

    return newTexture;
}

FSize SDLTexture::GetSize()
{
    Uint32 format;
    int access;
    int h;
    int w;

    SDL_QueryTexture(texture, &format, &access, &w, &h);

    FSize ret = FSize(h, w);
    
    return ret;
}

void SDLTexture::SetSolidColor(uint32_t pixelColor)
{
    int res = 0;
    const char* errorString;
    SDL_Surface* newSurface;
    SDL_Texture* newTexture;

    newSurface = SDL_CreateRGBSurface(0, Width, Height, 32, 0, 0, 0, 0);

    if (newSurface == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to set create RGB surface [%s] with error %s\n", TexturePath, errorString);

        return;
    }
    
    res = SDL_FillRect(newSurface, NULL, pixelColor);

    if (res == -1)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to set solid color to texture [%s] with error %s\n", TexturePath, errorString);

        return;
    }

    SDL_Renderer* renderer = Graphics->gameRenderer;

    newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);

    if (texture == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to set create texture [%s] with error %s\n", TexturePath, errorString);

        return;
    }

    surface = newSurface;
    texture = newTexture;
}
