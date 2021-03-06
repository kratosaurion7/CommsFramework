#include "FontProcessor.h"

#include <stdio.h>
#include <string>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"
#include "Geometry/FRectangle.h"
#include "Graphic/SDL/SDLUtilities.h"
#include "Graphic/SDL/SDLTexture.h"
#include "Graphic/Base Classes/BaseFont.h"

FontProcessor::FontProcessor()
{
    strcpy(CharacterSet, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
}


FontProcessor::~FontProcessor()
{
}

BaseList<BaseTexture*>* FontProcessor::GetCharactersFromFont(BaseTexture* inTexture)
{
    SDLTexture* tex = dynamic_cast<SDLTexture*>(inTexture);

    if (tex == NULL) // Texture needs to be in SDL Format
        return NULL;

    BaseList<BaseTexture*>* characterTextures = new BaseList<BaseTexture*>();

    SDL_Surface* font = tex->surface;

    if (font == NULL)
    {
        fprintf(stderr, "File not found or not correct image format.\n");
        return NULL;
    }

    if (font->format->BitsPerPixel != 32)
    {
        fprintf(stderr, "Pixel format is not 32bit.\n");
        return NULL;
    }

    Uint32* pix = (Uint32*)font->pixels;

    FRectangle* charRectangle;
    int currentCharIndex = 0;

    State = SEEKING;

    int i = 0, j = 0;

    int iters = 0;

    while (true)
    {
        if (i >= font->w)
        {
            return NULL;
        }

        Uint32 px = pix[i + (j * font->w)];

        switch (State)
        {
            case SEEKING:
            {
                if (j >= font->h)
                {
                    i++;
                    j = 0;
                }
                else
                {
                    if (px != BLANK)
                    {
                        State = BEGIN_CHAR;
                    }
                    else
                    {
                        j++;
                    }
                }

                break;
            }
            case BEGIN_CHAR:
            {
                charRectangle = new FRectangle();
                charRectangle->Left = (float)i;
                charRectangle->Top = (float)j;
                charRectangle->Right = (float)i;
                charRectangle->Bottom = (float)j;

                State = PIXEL_FOUND;

                break;
            }
            case LINE_SEEK:
            {
                if (j >= font->h)
                {
                    if (charRectangle->Right != i)
                    {
                        State = END_CHAR;
                    }

                    i++;
                    j = 0;
                }
                else
                {
                    if (px != BLANK)
                    {
                        State = PIXEL_FOUND;
                        break;
                    }

                    j++;
                }

                break;
            }
            case PIXEL_FOUND:
            {
                if (j >= font->h)
                {
                    State = LINE_SEEK;
                    break;
                }

                if (px != BLANK)
                {
                    if (j < charRectangle->Top)
                    {
                        charRectangle->Top = (float)j;
                    }
                    if (j > charRectangle->Bottom)
                    {
                        charRectangle->Bottom = (float)j;
                    }
                    if (i > charRectangle->Right)
                    {
                        charRectangle->Right = (float)i;
                    }
                }

                j++;

                break;
            }
            case END_CHAR:
            {
                SDL_Rect rec = FRectToSDL_Rect(*charRectangle);
                rec.w += 1; // Have to add +1 to w and h to compensate the comversion from my rec to sdl rec. TODO : Problem in FRect impl ?
                rec.h += 1;

                SDL_Surface* subSurf = SDL_CreateRGBSurface(0, rec.w, rec.h, 32, font->format->Rmask, font->format->Gmask, font->format->Bmask, font->format->Amask);

                SDL_BlitSurface(font, &rec, subSurf, NULL);

                SDLTexture* characterTexture = new SDLTexture();
                characterTexture->LoadFromSurface(subSurf);

                characterTextures->Add(characterTexture);

                currentCharIndex++;

                State = SEEKING;

                break;
            }
        }

        iters++;
    }

    return characterTextures;
}

BaseList<SpriteFontGlyph*>* FontProcessor::GetCharacterDescriptors(BaseTexture * inTexture)
{
    SDLTexture* tex = dynamic_cast<SDLTexture*>(inTexture);

    if (tex == NULL) // Texture needs to be in SDL Format
        return NULL;

    BaseList<SpriteFontGlyph*>* descriptorsList = new BaseList<SpriteFontGlyph*>();

    SDL_Surface* font = tex->surface;

    if (font == NULL)
    {
        fprintf(stderr, "File not found or not correct image format.\n");
        return NULL;
    }

    if (font->format->BitsPerPixel != 32)
    {
        fprintf(stderr, "Pixel format is not 32bit.\n");
        return NULL;
    }

    Uint32* pix = (Uint32*)font->pixels;

    FRectangle* charRectangle;
    int currentCharIndex = 0;

    State = SEEKING;

    int i = 0, j = 0;

    int iters = 0;

    while (true)
    {
        if (i >= font->w)
        {
            return NULL;
        }

        Uint32 px = pix[i + (j * font->w)];

        switch (State)
        {
        case SEEKING:
        {
            if (j >= font->h)
            {
                i++;
                j = 0;
            }
            else
            {
                if (px != BLANK)
                {
                    State = BEGIN_CHAR;
                }
                else
                {
                    j++;
                }
            }

            break;
        }
        case BEGIN_CHAR:
        {
            charRectangle = new FRectangle();
            charRectangle->Left = (float)i;
            charRectangle->Top = (float)j;
            charRectangle->Right = (float)i;
            charRectangle->Bottom = (float)j;

            State = PIXEL_FOUND;

            break;
        }
        case LINE_SEEK:
        {
            if (j >= font->h)
            {
                if (charRectangle->Right != i)
                {
                    State = END_CHAR;
                }

                i++;
                j = 0;
            }
            else
            {
                if (px != BLANK)
                {
                    State = PIXEL_FOUND;
                    break;
                }

                j++;
            }

            break;
        }
        case PIXEL_FOUND:
        {
            if (j >= font->h)
            {
                State = LINE_SEEK;
                break;
            }

            if (px != BLANK)
            {
                if (j < charRectangle->Top)
                {
                    charRectangle->Top = (float)j;
                }
                if (j > charRectangle->Bottom)
                {
                    charRectangle->Bottom = (float)j;
                }
                if (i > charRectangle->Right)
                {
                    charRectangle->Right = (float)i;
                }
            }

            j++;

            break;
        }
        case END_CHAR:
        {
            SDL_Rect rec = FRectToSDL_Rect(*charRectangle);
            rec.w += 1; // Have to add +1 to w and h to compensate the comversion from my rec to sdl rec. TODO : Problem in FRect impl ?
            rec.h += 1;

            SDL_Surface* subSurf = SDL_CreateRGBSurface(0, rec.w, rec.h, 32, font->format->Rmask, font->format->Gmask, font->format->Bmask, font->format->Amask);

            SDL_BlitSurface(font, &rec, subSurf, NULL);

            SpriteFontGlyph* characterTexture = new SpriteFontGlyph();
            characterTexture->Value = &CharacterSet[currentCharIndex];
            characterTexture->H = (float)rec.h;
            characterTexture->W = (float)rec.w;
            characterTexture->X = (float)rec.x;
            characterTexture->Y = (float)rec.y;

            descriptorsList->Add(characterTexture);

            currentCharIndex++;

            State = SEEKING;

            break;
        }
        }

        iters++;
    }

    return descriptorsList;
}
