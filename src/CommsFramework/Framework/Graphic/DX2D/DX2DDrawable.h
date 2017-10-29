#pragma once

struct ID2D1Bitmap;

class DX2DDrawable
{
public:
    virtual ID2D1Bitmap* GetDrawableTexture() = 0;
};