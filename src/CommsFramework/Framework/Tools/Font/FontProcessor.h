#pragma once

class BaseTexture;
struct SpriteFontGlyph;

#include "Collections/BaseList.h"

#define BLANK 0x00FFFFFF

class FontProcessor
{
public:
    FontProcessor();
    ~FontProcessor();

    static char* CharacterSet;

    static BaseList<BaseTexture*>* GetCharactersFromFont(BaseTexture* inTexture);

    static BaseList<SpriteFontGlyph*>* GetCharacterDescriptors(BaseTexture* inTexture);

private:
    enum ProcessState
    {
        SEEKING,
        BEGIN_CHAR,
        LINE_SEEK,
        PIXEL_FOUND,
        END_CHAR,
    };

    static ProcessState State;

};

