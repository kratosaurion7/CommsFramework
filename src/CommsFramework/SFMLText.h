#pragma once

class BaseFont;

#include <string>
#include <cstdint>

#include <SFML\Graphics.hpp>

#include "FPosition.h"
#include "FSize.h"
#include "FRectangle.h"

#include "SFMLDrawable.h"
#include "BaseText.h"

class SFMLText : public BaseText, public SFMLDrawable
{
public:
    SFMLText();
    ~SFMLText();

    // BaseText
    std::string GetText();
    void SetText(std::string text);

    BaseFont* GetFont();
    void SetFont(BaseFont* font);

    int GetCharacterSize();
    void SetCharacterSize(int size);

    TextStyle GetStyle();
    void SetStyle(TextStyle style = TEXT_STYLE_REGULAR);

    uint32_t GetColor();
    void SetColor(uint32_t color);

    sf::Text* innerImpl;

    sf::Drawable* GetDrawableImplementation();

    void SetGraphicalFilter(int graphic_filter);

    virtual BaseTexture* GetTextImage();
private:
    std::string textString;
    std::string textStringWithLineWrappings;

    BaseFont* textFont;

    int characterSize;

    sf::Color* textColorImpl;
    uint32_t textColor;

    TextStyle currentStyle;

    void UpdateTextWrapping();

    void UpdateInnerImpl();
};

