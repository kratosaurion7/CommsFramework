#pragma once

#include <string>

#include <SDL_ttf.h>

#include "BaseFont.h"

class SDLFont : public BaseFont
{
public:
    SDLFont();
    ~SDLFont();

    TTF_Font* fontObject;

    virtual void LoadFontFile(std::string path);
};

