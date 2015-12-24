#include "SDLUtilities.h"

#include <SDL.h>

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