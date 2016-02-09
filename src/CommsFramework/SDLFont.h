#pragma once

#include <string>

#include "BaseFont.h"

#include <SDL_ttf.h>

class SDLFont : public BaseFont
{
public:
    SDLFont();
    ~SDLFont();

    TTF_Font* fontObject;

    virtual void LoadFontFile(std::string path);
};

