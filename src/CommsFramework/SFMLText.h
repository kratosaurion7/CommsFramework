#pragma once

#include <SFML\Graphics.hpp>

#include <string>
#include <cstdint>

#include "SFMLDrawable.h"
#include "BaseText.h"
#include "FPosition.h"
#include "FSize.h"
#include "FRectangle.h"


class SFMLText : public BaseText
{
public:
	SFMLText();
	~SFMLText();

	sf::Drawable* GetDrawableImplementation();

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

private:
	BaseFont* textFont;

	int characterSize;

	sf::Color* textColorImpl;
	uint32_t textColor;

	TextStyle currentStyle;

	void UpdateInnerImpl();
};

