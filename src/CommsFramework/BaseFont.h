#pragma once

class BaseTexture;

#include <string>

struct SpriteFontGlyph
{
    char* Value;

    float X;
    float Y;

    float H;
    float W;
};

class BaseFont
{
public:
    virtual void LoadFontFile(std::string path) = 0;

    virtual void LoadSpriteFont(BaseTexture* texture, SpriteFontGlyph** glyphs, int charactersCount);
};