#pragma once

#include "Graphic/Base Classes/BaseText.h"
#include "DX2DDrawable.h"

class DX2DText : public BaseText, public DX2DDrawable
{
    virtual std::string GetText();
    virtual void SetText(std::string text);

    virtual BaseFont* GetFont();
    virtual void SetFont(BaseFont* font);

    virtual int GetCharacterSize();
    virtual void SetCharacterSize(int size);

    virtual TextStyle GetStyle();
    virtual void SetStyle(TextStyle style = TEXT_STYLE_REGULAR);

    virtual uint32_t GetColor();
    virtual void SetColor(uint32_t color);

    virtual BaseTexture* GetTextImage();
};