#include <SDL.h>
#include <SDL_image.h>
#undef main

#include <stdio.h>
#include <string>
#include <FRectangle.h>
#include <SDLUtilities.h>

void ProcessFile(char* fileName);
void ProcessCharacterRec(FRectangle* rec, char ident);

#define BLANK 0x00FFFFFF

enum ProcessState
{
    SEEKING,
    BEGIN_CHAR,
    LINE_SEEK,
    PIXEL_FOUND,
    END_CHAR,
} State;

char CharacterSet[63] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        char* fontName = argv[1];

        ProcessFile(fontName);

    }
    else
    {
        fprintf(stderr, "No arguments passed to program.\n");
    }

    fprintf(stderr, "Program End.\n");

    char buf[128];
    scanf(buf, "%s");

}

void ProcessFile(char* fileName)
{
    SDL_Surface* font = IMG_Load(fileName);

    if (font == NULL)
    {
        fprintf(stderr, "File not found or not correct image format.\n");
        return;
    }

    if (font->format->BitsPerPixel != 32)
    {
        fprintf(stderr, "Pixel format is not 32bit.\n");
        return;
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
            return;
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
                charRectangle->Left = i;
                charRectangle->Top = j;
                charRectangle->Right = i;
                charRectangle->Bottom = j;

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
                        charRectangle->Top = j;
                    }
                    if (j > charRectangle->Bottom)
                    {
                        charRectangle->Bottom = j;
                    }
                    if (i > charRectangle->Right)
                    {
                        charRectangle->Right = i;
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

                char fileName[260];
                if (islower(CharacterSet[currentCharIndex]))
                {
                    sprintf(fileName, "letters/%c_.png", CharacterSet[currentCharIndex]);
                }
                else
                {
                    sprintf(fileName, "letters/%c.png", CharacterSet[currentCharIndex]);
                }

                IMG_SavePNG(subSurf, fileName);

                currentCharIndex++;

                State = SEEKING;

                break;
            }
        }

        iters++;
    }
}

void ProcessCharacterRec(FRectangle* rec, char ident)
{

}