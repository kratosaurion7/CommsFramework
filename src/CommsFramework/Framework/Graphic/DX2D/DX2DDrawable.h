#pragma once

struct IWICBitmapSource;

class DX2DDrawable
{
public:
    virtual IWICBitmapSource* GetDrawableTexture() = 0;
};