#include "SDLUtilities.h"

#include <SDL.h>

#include "SDLSprite.h"
#include "SDLText.h"
#include "FRectangle.h"
#include "FSize.h"

SDL_Rect FRectToSDL_Rect(FRectangle rec)
{
    FSize* recSiz = rec.Size();

    SDL_Rect newRect;
    newRect.h = recSiz->Height;
    newRect.w = recSiz->Width;
    newRect.x = rec.Left;
    newRect.y = rec.Top;

    delete(recSiz); // ...

    return newRect;
}

void SaveSpriteAsBMP(SDLSprite* sprt, std::string fileName)
{
    int res = SDL_SaveBMP(sprt->currentSpriteTexture->surface, fileName.c_str());

    if (res != 0)
    {
        const char* errorString = SDL_GetError();
        fprintf(stderr, "Unable to save sprite to bitmap with error %s\n", errorString);
    }

}

void SaveTextAsBMP(SDLText* text, std::string fileName)
{
    int res = SDL_SaveBMP(text->textSurface, fileName.c_str());

    if (res != 0)
    {
        const char* errorString = SDL_GetError();
        fprintf(stderr, "Unable to save text to bitmap with error %s\n", errorString);
    }
}
