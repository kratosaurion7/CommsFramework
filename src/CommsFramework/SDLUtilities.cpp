#include "SDLUtilities.h"

#include <SDL.h>

#include "SDLSprite.h"
#include "SDLText.h"
#include "FRectangle.h"
#include "FSize.h"

SDL_Rect FRectToSDL_Rect(FRectangle rec)
{
    FSize recSiz = rec.Size();

    SDL_Rect newRect;
    newRect.h = recSiz.Height;
    newRect.w = recSiz.Width;
    newRect.x = rec.Left;
    newRect.y = rec.Top;

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

void TestGraphical()
{
    float diagonalDpi = 0;
    float horizontalDpi = 0;
    float verticalDpi = 0;

    int res = SDL_GetDisplayDPI(0, &diagonalDpi, &horizontalDpi, &verticalDpi);

    char buf[256];
    sprintf(buf, "DDPI = %f, HDPI = %f, VDPI = %f\n", diagonalDpi, horizontalDpi, verticalDpi);

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "INFO", buf, NULL);
}
