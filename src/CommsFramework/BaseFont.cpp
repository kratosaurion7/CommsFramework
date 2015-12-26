#include "BaseFont.h"

#include "BaseTexture.h"

BaseFont::BaseFont()
{
    GlyphMap = NULL;
}

BaseFont::~BaseFont()
{
    if (GlyphMap != NULL)
    {
        GlyphMap->Clear();
        delete(GlyphMap);
    }
}

void BaseFont::LoadSpriteFont(BaseTexture* texture, SpriteFontGlyph** glyphs, int charactersCount)
{
    for (int i = 0; i < charactersCount; i++)
    {
        SpriteFontGlyph* glyph = glyphs[i];

        FRectangle rec = FRectangle(glyph->X, glyph->Y, glyph->H, glyph->W);
        
        BaseTexture* subTex = texture->GetSubTexture(rec);

        Pair<char, BaseTexture*>* newGlyphPair = new Pair<char, BaseTexture*>();
        newGlyphPair->Item1 = glyph->Value;
        newGlyphPair->Item2 = subTex;

        this->GlyphMap->Add(newGlyphPair);
    }

    FontType = SPRITE_FONT;
}

SpriteFontGlyph** BaseFont::BuildDefaultFontGlyphDescriptor(int & outLength)
{
    int defaultCharacterAmount = 26;

    SpriteFontGlyph** ret = new SpriteFontGlyph*[defaultCharacterAmount];

    for (int i = 0; i < defaultCharacterAmount; i++)
    {
        SpriteFontGlyph* sfg = new SpriteFontGlyph();

        sfg->H = 26;
        sfg->W = 50;
        
        sfg->X = 26 * i;
        sfg->Y = 0;

        sfg->Value = 65 + i;

        ret[i] = sfg;
    }

    outLength = defaultCharacterAmount;

    return ret;
}