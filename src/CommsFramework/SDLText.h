#pragma once

class BaseFont;
class DrawObject;

class SDLFont;

#include <string>
#include <cstdint>

#include "SDLDrawable.h"
#include "BaseText.h"

class SDLText : public BaseText, public SDLDrawable
{
public:
    SDLText();
    ~SDLText();

    virtual std::string GetText();
    virtual void SetText(std::string text);

    virtual BaseFont* GetFont();
    virtual void SetFont(BaseFont* newFont);

    virtual int GetCharacterSize();
    virtual void SetCharacterSize(int newSize);

    virtual TextStyle GetStyle();
    virtual void SetStyle(TextStyle style = TEXT_STYLE_REGULAR);

    virtual uint32_t GetColor();
    virtual void SetColor(uint32_t color);

    virtual SDL_Texture* GetDrawableTexture();
    virtual void UpdateInnerImpl();

private:
    std::string textContent;

    SDLFont* font;

    int characterSize;

    TextStyle sdlTextStyle;

    uint32_t foregroundColor;

    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
};

