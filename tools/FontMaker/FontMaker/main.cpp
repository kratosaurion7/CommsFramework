#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

#undef main

void ProcessFile(char* fileName);

enum ProcessState
{
    SEEKING,
    CHAR_FOUND,
    CHAR_END
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
    SDL_LockSurface(font);

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
            //pix[i + (j * font->w)] = 0xFF0000FF;
            
            int test = 0;

            //if (i < 100)
            //{
            //    char buf[260];
            //    sprintf(buf, "%d.png", i);
            //    IMG_SavePNG(font, buf);
            //}
        }
        
    }

    SDL_UnlockSurface(font);

}