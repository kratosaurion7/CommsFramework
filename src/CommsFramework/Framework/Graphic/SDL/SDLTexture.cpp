#include "SDLTexture.h"

#include "SDLUtilities.h"
#include "SDLGraphicEngine.h"

SDLTexture* SDLTexture::MissingTextureSingleton;

SDLTexture::SDLTexture()
{
    surface = NULL;
    texture = NULL;
    Engine = NULL;
}

SDLTexture::~SDLTexture()
{
    if (texture != NULL)
        SDL_DestroyTexture(texture);

    if (surface != NULL)
        SDL_FreeSurface(surface);
}

SDL_Texture* SDLTexture::GetMissingTextureTexture(BaseGraphicEngine* engine)
{
    if (SDLTexture::MissingTextureSingleton == NULL)
    {
        SDLTexture* tex = (SDLTexture*)engine->CreateTexture("Missing_Texture");

        tex->Load("assets/engine/missing_texture.png");
        
        SDLTexture::MissingTextureSingleton = tex;
    }

    return SDLTexture::MissingTextureSingleton->texture;
}

void SDLTexture::Initalize(float width, float height)
{
    Height = (int)height;
    Width = (int)width;
}

int SDLTexture::Load(std::string path)
{    
    int res = 0;
    const char* errorString;

    surface = IMG_Load(path.c_str());

    if (surface == NULL)
    {

        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create surface for [%s] with error %s\n", path.c_str(), errorString);

        return 1;
    }

    SDL_Renderer* renderer = Graphics->gameRenderer;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create texture for [%s] with error %s\n", path.c_str(), errorString);

        return 1;
    }

    // TODO : Check if we keep both the Texture and Surface in memory
    // SDL_FreeSurface(surface); // Must keep surface to use GetSubTexture()
    TexturePath = path;
    this->Height = surface->h;
    this->Width = surface->w;

    return 0;
}

void SDLTexture::LoadFromMemory(char* data, int dataSize)
{
}

void SDLTexture::LoadFromSurface(SDL_Surface* srcSurface)
{
    const char* errorString;
    SDL_Renderer* renderer = Graphics->gameRenderer;

    this->surface = srcSurface;
    texture = SDL_CreateTextureFromSurface(renderer, srcSurface);

    if (texture == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create texture from surface with error %s\n", errorString);

        return;
    }

    this->Height = surface->h;
    this->Width = surface->w;

    TexturePath = "";
}

BaseTexture* SDLTexture::GetSubTexture(FRectangle rec)
{
    int res = 0;
    const char* errorString;
    SDLTexture* newTexture;

    FSize recSize = rec.Size();
    SDL_Rect sRec = FRectToSDL_Rect(rec);

    SDL_Surface* subTextureSurface = SDL_CreateRGBSurface(0, (int)recSize.Width, (int)recSize.Height, 32, rmask, gmask, bmask,amask);
    //SDL_Surface* subTextureSurface = SDL_CreateRGBSurface(0, recSize->Width, recSize->Height, 32, 0, 0, 0, 0);
    
    if (subTextureSurface == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create RGB surface with error %s\n", errorString);

        return NULL;
    }

    Uint32 color = SDL_MapRGBA(subTextureSurface->format, 255, 255, 255, 255);

    SDL_FillRect(subTextureSurface, NULL, color);

    res = SDL_BlitSurface(this->surface, &sRec, subTextureSurface, NULL);

    //IMG_SavePNG(this->surface, "src.png");
    //IMG_SavePNG(subTextureSurface, "dst.png");


    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to blit surface with error %s\n", errorString);

        return NULL;
    }

    newTexture = (SDLTexture*)this->Engine->CreateTexture();
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

    FSize ret = FSize((float)h, (float)w);
    
    return ret;
}

void SDLTexture::SetSolidColor(uint32_t pixelColor)
{
    int res = 0;
    const char* errorString;
    SDL_Surface* newSurface;
    SDL_Texture* newTexture;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    newSurface = SDL_CreateRGBSurface(0, Width, Height, 32, rmask, gmask, bmask, amask);

    if (newSurface == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to set create RGB surface [%s] with error %s\n", TexturePath.c_str(), errorString);

        return;
    }
    
    res = SDL_FillRect(newSurface, NULL, pixelColor);

    if (res == -1)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to set solid color to texture [%s] with error %s\n", TexturePath.c_str(), errorString);

        return;
    }

    SDL_Renderer* renderer = Graphics->gameRenderer;

    newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);

    if (newTexture == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to set create texture [%s] with error %s\n", TexturePath.c_str(), errorString);

        return;
    }

    surface = newSurface;
    texture = newTexture;
}

void SDLTexture::ResetTextureFromSurface()
{
    SDL_Renderer* renderer = Graphics->gameRenderer;

    if (surface != NULL)
    {
        FreeTexture();

        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
}

void SDLTexture::FreeTexture()
{
    if (this->texture != NULL)
        SDL_DestroyTexture(texture);
}

void SDLTexture::SaveTextureToFile()
{
    this->SaveTextureToFile("out.bmp");
}

void SDLTexture::SaveTextureToFile(std::string fileName)
{
    int res = SDL_SaveBMP(this->surface, fileName.c_str());

    if (res != 0)
    {
        const char* errorString = SDL_GetError();
        fprintf(stderr, "Unable to save file to file, %s\n", errorString);
    }
}

void SDLTexture::OverlayTexture(BaseTexture* other)
{
    SDLTexture* sdlOther = (SDLTexture*)other;

    SDL_Surface* surf = sdlOther->surface;

    SDL_BlendMode currentBlend;
    int res = SDL_GetSurfaceBlendMode(this->surface, &currentBlend);

    if (res != 0)
    {

    }

    res = SDL_SetSurfaceBlendMode(this->surface, SDL_BLENDMODE_BLEND);

    if (res != 0)
    {

    }
    
    SDL_Rect rec;
    rec.h = surf->h;
    rec.w = surf->w;
    rec.x = 0;
    rec.y = 0;

    other->SaveTextureToFile("test.png");
    res = SDL_BlitSurface(surf, NULL, this->surface, NULL);

    this->SaveTextureToFile("test.png");

    if (res != 0)
    {
        auto errorString = SDL_GetError();
        fprintf(stderr, "Unable to set solid color to texture [%s] with error %s\n", TexturePath.c_str(), errorString);
    }

    res = SDL_SetSurfaceBlendMode(this->surface, currentBlend);


    return;
    
    Uint32* myPix = (Uint32*)this->surface->pixels;
    Uint32* pix = (Uint32*)surf->pixels;

    for (int i = 0; i < this->Height; i++)
    {
        for (int j = 0; j < this->Width; j++)
        {
            if (i > other->GetSize().Height || j > other->GetSize().Width)
            {
                continue;
            }

            Uint32 blendedPix;
            Uint32 myP = myPix[j + (i * this->Height)];
            Uint32 otP = pix[j + (i * this->Height)];

            //dstRGB = (srcRGB * srcA) + (dstRGB * (1 - srcA))
            //dstA = srcA + (dstA * (1 - srcA))

            // TODO : Blend both pixels based on alpha
            blendedPix = ((myP & (rmask | gmask | amask)) * (myP & amask)) + ((otP & (rmask | gmask | amask) * (1 - (myP & amask)))) & (rmask | gmask | amask);

            myPix[j + (i * this->Height)] = blendedPix;
        }
    }

    SDL_UnlockSurface(this->surface);

    ResetTextureFromSurface();
}
