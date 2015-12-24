#pragma once

class BaseFont;
class DrawObject;

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
    virtual void SetFont(BaseFont* font);

    virtual int GetCharacterSize();
    virtual void SetCharacterSize(int size);

    virtual TextStyle GetStyle();
    virtual void SetStyle(TextStyle style = TEXT_STYLE_REGULAR);

    virtual uint32_t GetColor();
    virtual void SetColor(uint32_t color);

    virtual SDL_Texture* GetDrawableTexture();
    virtual void UpdateInnerImpl();

};

