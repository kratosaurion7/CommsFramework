#pragma once

//enum COLOR_MAP_TYPE
//{
//    NO_COLOR_MAP = 0,
//    COLOR_MAP_PRESENT = 1,
//};
//
//enum IMAGE_TYPE
//{
//    NO_DATA = 0,
//    COLOR_MAP = 1,
//    TRUE_COLOR = 2,
//    GRAYSCALE = 3,
//    RLE_COLOR_MAP = 9,
//    RLE_TRUE_COLOR = 10,
//    RLE_GRAYSCALE = 11,
//};

struct TgaFileHeader {
    char  idlength;
    char  colourmaptype;
    char  datatypecode;
    short colourmaporigin;
    short colourmaplength;
    char  colourmapdepth;
    short x_origin;
    short y_origin;
    short width;
    short height;
    char  bitsperpixel;
    char  imagedescriptor;
};

struct TgaPix {
    unsigned char b, g, r, a;
};

class TgaFile
{
public:
    TgaFile();
    ~TgaFile();

    TgaFileHeader* Header;
    TgaPix** Pixels;

    int PixelCount;
    

    void Init(short int w, short int h);

    void Save();

    void Clear();

    
};

