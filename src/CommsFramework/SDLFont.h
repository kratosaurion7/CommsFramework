#pragma once

#include <string>

#include "BaseFont.h"

class SDLFont : public BaseFont
{
public:
    SDLFont();
    ~SDLFont();

    virtual void Load(std::string path);
};

