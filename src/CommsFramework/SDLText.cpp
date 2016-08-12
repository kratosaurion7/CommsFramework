#include "SDLText.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "SDLFont.h"
#include "FRectangle.h"
#include "BaseTexture.h"
#include "SDLTexture.h"
#include "BaseGraphicEngine.h"
#include "SDLGraphicEngine.h"
#include "SDLUtilities.h"

SDLText::SDLText()
{
    isVisible = false;
    position = FPosition();
    positionOffset = FPosition();
    size = FSize();
    scale = FloatVec();
    scale.Set(1, 1);
    clippingBounds = FRectangle();

    textContent = "";
    font = NULL;
    characterSize = 12;
    sdlTextStyle = TEXT_STYLE_REGULAR;
    foregroundColor = 0xFFFFFFFF;
    textSurface = NULL;
    textTexture = NULL;

    Engine = NULL;
    ClickInfo = NULL;
}

SDLText::~SDLText()
{
}

std::string SDLText::GetText()
{
    return textContent;
}

void SDLText::SetText(std::string text)
{
    if (textContent.compare(text) != 0)
    {
        textContent = text;
        
        this->UpdateInnerImpl();
    }
}

BaseFont* SDLText::GetFont()
{
    return font;
}

void SDLText::SetFont(BaseFont* newFont)
{
    SDLFont* convertedFont = dynamic_cast<SDLFont*>(newFont);

    if (convertedFont != NULL)
    {
        this->font = convertedFont;
    }

    UpdateInnerImpl();
}

int SDLText::GetCharacterSize()
{
    return characterSize;
}

void SDLText::SetCharacterSize(int newSize)
{
    if (characterSize != newSize)
    {
        characterSize = newSize;

        UpdateInnerImpl();
    }
}

TextStyle SDLText::GetStyle()
{
    return sdlTextStyle;
}

void SDLText::SetStyle(TextStyle style)
{
    if (sdlTextStyle != style)
    {
        sdlTextStyle = style;

        UpdateInnerImpl();
    }
}

uint32_t SDLText::GetColor()
{
    return foregroundColor;
}

void SDLText::SetColor(uint32_t color)
{
    if (foregroundColor != color)
    {
        foregroundColor = color;

        UpdateInnerImpl();
    }
}

SDL_Texture* SDLText::GetDrawableTexture()
{
    return textTexture;
}

void SDLText::UpdateInnerImpl()
{
    if (this->font == NULL || this->characterSize <= 0)
        return;

    if (this->font->FontType == BaseFont::FONT_FILE)
    {
        SDL_Color color = { 0,0,0,0 };
        color.a = (this->foregroundColor &  0xFF000000) >> 24;
        color.r = (this->foregroundColor &  0x00FF0000) >> 16;
        color.g = (this->foregroundColor) & 0x0000FF00 >> 8;
        color.b = (this->foregroundColor) & 0x000000FF;
        SDL_Surface* renderedSurface = TTF_RenderText_Solid(this->font->fontObject, this->textContent.c_str(), color);

        if (renderedSurface == NULL)
        {
            const char* errorString = TTF_GetError();
            fprintf(stderr, "Could not render font with error %s\n", errorString);

            delete(errorString);
            return;
        }
        
        this->SetSize(renderedSurface->h, renderedSurface->w);

        SDL_Renderer* renderer = ((SDLGraphicEngine*)Engine)->gameRenderer;
        SDL_FreeSurface(textSurface);
        textSurface = renderedSurface;

        SDL_DestroyTexture(textTexture);
        textTexture = SDL_CreateTextureFromSurface(renderer, renderedSurface);
    }
    else if (this->font->FontType == BaseFont::SPRITE_FONT)
    {
        int finalTextWidth = 0;
        int finalTextHeight = 0;

        finalTextWidth = this->textContent.length() * fallbackFontWidth;
        finalTextHeight = fallbackFontHeight; // Test height of 50, maybe this will be provided by the font

        Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

        SDL_Surface* finalTextSurface = SDL_CreateRGBSurface(0, finalTextWidth, finalTextHeight, 32, rmask, gmask, bmask, amask);
    
        SDL_FillRect(finalTextSurface, NULL, 0xFFFFFFFF);

        FPosition* currentSpaceRectangle = new FPosition(0, 0);

        for (int i = 0; i < this->textContent.length();i++)
        {
            BaseTexture* characterTexture;
            char textCharacter = this->textContent.at(i);

            if (strncmp(&textCharacter, " ", 1) == 0)
            {
                currentSpaceRectangle->X += fallbackFontWidth;

                continue;
            }

            for (int y = 0; y < this->font->GlyphMap->Count();y++)
            {
                Pair<char*, BaseTexture*>* iteratedPair = this->font->GlyphMap->Get(y);
                char* iteratedCharacter = iteratedPair->Item1;

                if (strncmp(&textCharacter, iteratedCharacter, 1) == 0)
                {
                    characterTexture = iteratedPair->Item2;
                    break;
                }
                else 
                {
                    characterTexture = NULL;
                }
            }

            if (characterTexture == NULL) 
            {
                currentSpaceRectangle->X += fallbackFontWidth;
                continue;
            }

            SDLTexture* convertedCharacterTexture = dynamic_cast<SDLTexture*>(characterTexture);
        
            SDL_Rect destRec = SDL_Rect();
            destRec.x = currentSpaceRectangle->X;
            destRec.y = currentSpaceRectangle->Y;
            destRec.h = fallbackFontHeight;
            destRec.w = fallbackFontWidth;
            int res = SDL_BlitScaled(convertedCharacterTexture->surface, NULL, finalTextSurface, &destRec);

            if (res != 0)
            {
                const char* errorString = SDL_GetError();
                fprintf(stderr, "Unable to scaled blit with error %s\n", errorString);
            }

            currentSpaceRectangle->X += fallbackFontWidth;

        }

        if (textTexture != NULL)
            SDL_DestroyTexture(this->textTexture);

        if (textSurface != NULL)
            SDL_FreeSurface(textSurface);

        this->SetSize(finalTextHeight, finalTextWidth);
    
        SDL_Renderer* renderer = ((SDLGraphicEngine*)Engine)->gameRenderer;
        textSurface = finalTextSurface;
        textTexture = SDL_CreateTextureFromSurface(renderer, finalTextSurface);

        delete(currentSpaceRectangle);
    }

}

void SDLText::SetGraphicalFilter(int graphic_filter)
{

}

BaseTexture* SDLText::GetTextImage()
{
    SDLTexture* tex = new SDLTexture();
    tex->Graphics = (SDLGraphicEngine*)this->Engine;
    tex->Engine = this->Engine;

    tex->LoadFromSurface(this->textSurface);

    return tex;
}
