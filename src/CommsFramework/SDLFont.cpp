#include "SDLFont.h"

#include <SDL_ttf.h>

SDLFont::SDLFont()
{
}


SDLFont::~SDLFont()
{
}

void SDLFont::LoadFontFile(std::string path)
{
    fontObject = TTF_OpenFont(path.c_str(), 22);

    if (!fontObject)
    {
        const char* errorString = TTF_GetError();
        fprintf(stderr, "Cannot open font file %s with error %s\n", path.c_str(), errorString);

        delete(errorString);

        return;
    }

    FontType = FONT_FILE;
}