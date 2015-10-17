#include "SFMLText.h"

#include "SFMLFont.h"

#include "FPosition.h"
#include "FSize.h"
#include "FRectangle.h"

SFMLText::SFMLText()
{
    innerImpl = new sf::Text();
    textFont = NULL;
    textColorImpl = NULL;
    isVisible = true;
    currentStyle = TEXT_STYLE_REGULAR;
    scale.Set(1, 1);

}


SFMLText::~SFMLText()
{
    delete innerImpl;
}

std::string SFMLText::GetText()
{
    return innerImpl->getString();
}

void SFMLText::SetText(std::string text)
{
    innerImpl->setString(text);
}

BaseFont * SFMLText::GetFont()
{
    return textFont;
}

void SFMLText::SetFont(BaseFont * font)
{
    SFMLFont* sfmlFont = dynamic_cast<SFMLFont*>(font);

    if (sfmlFont != NULL)
    {
        textFont = font;

        innerImpl->setFont(*(sfmlFont->innerImpl));
    }
}

int SFMLText::GetCharacterSize()
{
    return characterSize;
}

void SFMLText::SetCharacterSize(int size)
{
    characterSize = size;
    innerImpl->setCharacterSize(size);
}

TextStyle SFMLText::GetStyle()
{
    return currentStyle;
}

void SFMLText::SetStyle(TextStyle style)
{
    currentStyle = style;
}

uint32_t SFMLText::GetColor()
{
    return textColor;
}

void SFMLText::SetColor(uint32_t color)
{
    textColor = color;
    textColorImpl = new sf::Color(color);

    innerImpl->setColor(*textColorImpl);
}

sf::Drawable* SFMLText::GetDrawableImplementation()
{
    return innerImpl;
}

void SFMLText::UpdateInnerImpl()
{
    this->innerImpl->setPosition(GetX() + GetOffsetX(), GetY() + GetOffsetY());
    this->innerImpl->setScale(GetScale().X, GetScale().Y);
}