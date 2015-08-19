#pragma once

#include <string>
#include <cstdint>


#include "BaseFont.h"

#include "DrawObject.h"

enum TextStyle {
    TEXT_STYLE_REGULAR,
    TEXT_STYLE_BOLD,
    TEXT_STYLE_ITALIC
};

class BaseText : public DrawObject
{
public:
    virtual std::string GetText() = 0;
    virtual void SetText(std::string text) = 0;

    virtual BaseFont* GetFont() = 0;
    virtual void SetFont(BaseFont* font) = 0;

    virtual int GetCharacterSize() = 0;
    virtual void SetCharacterSize(int size) = 0;

    virtual TextStyle GetStyle() = 0;
    virtual void SetStyle(TextStyle style = TEXT_STYLE_REGULAR) = 0;

    virtual uint32_t GetColor() = 0;
    virtual void SetColor(uint32_t color) = 0;
};