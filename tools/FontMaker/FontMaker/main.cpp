#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

#undef main

void ProcessFile(char* fileName);

enum ProcessState
{
    SEEKING,

};

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

    Uint32* pix = (Uint32*)font->pixels;

    for (int i = 0; i < font->w; i++)
    {
        for (int j = 0; j < font->h; j++)
        {
            Uint32 px = pix[i + (j * font->w)];

            if (px == 0xFFFFFFFF)
            {
                int test = 5;
            }

            int test = 0;
        }
    }

}