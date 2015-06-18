#pragma once

#include <SFML\Graphics.hpp>

#include <string>
#include <cstdint>


#include "BaseText.h"
#include "FPosition.h"
#include "FSize.h"
#include "FRectangle.h"


class SFMLText : public BaseText
{
public:
	SFMLText();
	~SFMLText();

	// DrawObject
	void Show(bool show);
	bool IsVisible();

	float GetX();
	float GetY();

	void SetX(float value);
	void SetY(float value);

	void IncrementX(float value);
	void IncrementY(float value);

	FPosition* GetPos();
	void SetPos(float x, float y);
	void SetPos(FPosition* value);
	void SetCenterPos(FPosition* value);

	FRectangle* GetRectangle();

	float GetHeight();
	float GetWidth();

	void SetHeight(float height);
	void SetWidth(float width);

	FSize* GetSize();
	void SetSize(float height, float width);
	void SetSize(FSize* value);

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

	bool isVisible;

	FPosition* position;
	FSize* size;

	int characterSize;

	sf::Color* textColorImpl;
	uint32_t textColor;

	TextStyle currentStyle;

	void UpdateInnerImpl();
};

