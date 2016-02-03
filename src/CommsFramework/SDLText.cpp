#include "SDLText.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_render.h>

#include "SDLFont.h"
#include "FRectangle.h"
#include "BaseTexture.h"
#include "SDLTexture.h"
#include "BaseGraphicEngine.h"
#include "SDLGraphicEngine.h"

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

    int finalTextWidth = 0;
    int finalTextHeight = 0;

    finalTextWidth = this->textContent.length() * 30;
    finalTextHeight = 50; // Test height of 50, maybe this will be provided by the font

    SDL_Surface* finalTextSurface = SDL_CreateRGBSurface(0, finalTextWidth, finalTextHeight, 32, 0, 0, 0, 0);
    SDL_FillRect(finalTextSurface, NULL, 0xFFFFFFFF);

    FPosition* currentSpaceRectangle = new FPosition(0, 0);

    for (int i = 0; i < this->textContent.length();i++)
    {
        BaseTexture* characterTexture;
        char textCharacter = this->textContent.at(i);

        if (strcmp(&textCharacter, " ") == 0)
        {
            currentSpaceRectangle->X += 30;

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
            continue;

        SDLTexture* convertedCharacterTexture = dynamic_cast<SDLTexture*>(characterTexture);
        
        SDL_Rect destRec = SDL_Rect();
        destRec.x = currentSpaceRectangle->X;
        destRec.y = currentSpaceRectangle->Y;
        destRec.h = 50;
        destRec.w = 30;
        int res = SDL_BlitSurface(convertedCharacterTexture->surface, NULL, finalTextSurface, &destRec);

        if (res != 0)
        {
            const char* errorString = SDL_GetError();
            fprintf(stderr, "Unable to create RGB surface with error %s\n", errorString);
        }

        currentSpaceRectangle->X += 30;

    }

    //if(textTexture != NULL)
    //    delete(textTexture);

    //if (textSurface != NULL)
    //    delete(textSurface);

    
    
    SDL_Renderer* renderer = ((SDLGraphicEngine*)Engine)->gameRenderer;
    textSurface = finalTextSurface;
    textTexture = SDL_CreateTextureFromSurface(renderer, finalTextSurface);

    delete(currentSpaceRectangle);

    //if (textSurface != NULL)
    //{
    //    SDL_SaveBMP(textSurface, "out.bmp");
    //}

}