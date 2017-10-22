#pragma once

#include "Graphic/Base Classes/BaseFont.h"

class DX2DFont : public BaseFont
{
public:
    DX2DFont();
    ~DX2DFont();
    
    virtual void LoadFontFile(std::string path);
};