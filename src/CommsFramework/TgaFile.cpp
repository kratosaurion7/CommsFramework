#include "TgaFile.h"

#include <cstdio>
#include <fstream>

TgaFile::TgaFile()
{
    Header = new TgaFileHeader();
    Header->idlength = 0;
    Header->colourmaptype = 0;// NO_COLOR_MAP;
    Header->datatypecode = 2;// TRUE_COLOR;
    Header->colourmaporigin = 0;
    Header->colourmaplength = 0;
    Header->colourmapdepth = 0;
    Header->x_origin = 0;
    Header->y_origin = 0;
    Header->width = 100;
    Header->height = 100;
    Header->bitsperpixel = 32;
    Header->imagedescriptor = 8;


    Pixels = new TgaPix*[100 * 100];
    for (int i = 0; i < 100 * 100; i++)
    {
        TgaPix* px = new TgaPix();
        px->a = 128;
        px->b = 255;
        px->g = 0;
        px->r = 0;

        Pixels[i] = px;
    }
}


TgaFile::~TgaFile()
{
}

void TgaFile::Save()
{
    std::fstream out = std::fstream("out.tga", std::ios::out | std::ios::binary);
    out.write(&Header->idlength, 1);
    out.write(&Header->colourmaptype, 1);
    out.write(&Header->datatypecode, 1);
    out.write((char*)&Header->colourmaporigin, 2);
    out.write((char*)&Header->colourmaplength, 2);
    out.write(&Header->colourmapdepth, 1);
    out.write((char*)&Header->x_origin, 2);
    out.write((char*)&Header->y_origin, 2);
    out.write((char*)&Header->width, 2);
    out.write((char*)&Header->height, 2);
    out.write(&Header->bitsperpixel, 1);
    out.write(&Header->imagedescriptor, 1);

    for (int i = 0; i < 100 * 100; i++)
    {
        char* pixelData = (char*)Pixels[i];
        out.write(pixelData, sizeof(TgaPix));
    }

    out.close();
}
