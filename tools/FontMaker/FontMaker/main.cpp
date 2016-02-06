#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

#undef main

void ProcessFile(char* fileName);

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

}