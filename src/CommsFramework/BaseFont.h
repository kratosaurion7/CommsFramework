#pragma once

#include <string>

class BaseFont
{
public:
    virtual void Load(std::string path) = 0;
};