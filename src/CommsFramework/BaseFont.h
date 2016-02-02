#pragma once

class BaseTexture;

#include <string>

#include "PointerList.h"
#include "Pair.h"

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
    enum FontTypes
    {
        FONT_FILE,
        SPRITE_FONT
    } FontType;

    BaseFont();
    ~BaseFont();

    PointerList<Pair<char*, BaseTexture*>*>* GlyphMap;

    virtual void LoadFontFile(std::string path) = 0;

    virtual void LoadSpriteFont(BaseTexture* fontTexture, SpriteFontGlyph** glyphs, int charactersCount);

    static SpriteFontGlyph** BuildDefaultFontGlyphDescriptor(int& outLength);
};