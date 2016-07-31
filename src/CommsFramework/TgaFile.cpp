#include "TgaFile.h"

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
    Header->width = 0;
    Header->height = 0;
    Header->bitsperpixel = 32;
    Header->imagedescriptor = 32;
}


TgaFile::~TgaFile()
{
    delete(Header);
    
    for (int i = 0; i < Width * Height; i++)
    {
        TgaPix* px = Pixels[i];
        
        delete(px);
    }

    delete(Pixels);
}

void TgaFile::Init(short int w, short int h)
{
    Width = w;
    Height = h;

    Header->width = w;
    Header->height = h;

    Pixels = new TgaPix*[Width * Height];
    for (int i = 0; i < Width * Height; i++)
    {
        TgaPix* px = new TgaPix();
        px->a = 255;
        px->b = 255;
        px->g = 255;
        px->r = 255;

        Pixels[i] = px;
    }
}

void TgaFile::Save(std::string fileName)
{
    std::fstream out = std::fstream(fileName, std::ios::out | std::ios::binary);
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

    for (int i = 0; i < Width * Height; i++)
    {
        char* pixelData = (char*)Pixels[i];
        out.write(pixelData, sizeof(TgaPix));
    }

    out.close();
}

void TgaFile::Clear()
{
    for (int i = 0; i < Width * Height; i++)
    {
        TgaPix* px = Pixels[i];
        px->a = 255;
        px->b = 0;
        px->g = 0;
        px->r = 0;
    }
}

void TgaFile::FillColor(short int r, short int g, short int b, short int a)
{
    for (int i = 0; i < Width * Height; i++)
    {
        TgaPix* px = Pixels[i];
        px->a = a;
        px->b = b;
        px->g = g;
        px->r = r;
    }
}

void TgaFile::FillColor(TgaPix * pixColor)
{
    for (int i = 0; i < Width * Height; i++)
    {
        TgaPix* px = Pixels[i];
        px->a = pixColor->a;
        px->b = pixColor->b;
        px->g = pixColor->g;
        px->r = pixColor->r;
    }
}

TgaPix* TgaFile::Get(int x, int y)
{
    return Pixels[x + (y * Width)];
}

void TgaFile::Set(TgaPix * px, int x, int y)
{
    TgaPix* pixel = this->Get(x, y);
    pixel->a = px->a;
    pixel->r = px->r;
    pixel->g = px->g;
    pixel->b = px->b;
}
