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
	position = new FPosition();
	size = new FSize();
}


SFMLText::~SFMLText()
{
	delete innerImpl;
	delete position;
	delete size;
}

void SFMLText::Show(bool show)
{
	isVisible = show;
}

bool SFMLText::IsVisible()
{
	return isVisible;
}

float SFMLText::GetX()
{
	if (position != NULL)
	{
		return position->X;
	}
	else
	{
		return 0;
	}
}

float SFMLText::GetY()
{
	if (position != NULL)
	{
		return position->Y;
	}
	else
	{
		return 0;
	}
}

void SFMLText::SetX(float value)
{
	if (position != NULL)
	{
		position->X = value;

		UpdateInnerImpl();
	}
}

void SFMLText::SetY(float value)
{
	if (position != NULL)
	{
		position->Y = value;

		UpdateInnerImpl();
	}
}

void SFMLText::IncrementX(float value)
{
	if (position != NULL)
	{
		position->X += value;

		UpdateInnerImpl();
	}
}

void SFMLText::IncrementY(float value)
{
	if (position != NULL)
	{
		position->Y += value;

		UpdateInnerImpl();
	}
}

FPosition * SFMLText::GetPos()
{
	return position;
}

void SFMLText::SetPos(float x, float y)
{
	if (position != NULL)
	{
		position->Set(x, y);

		UpdateInnerImpl();
	}
}

void SFMLText::SetPos(FPosition* value)
{
	if (position != NULL)
		delete position;

	position = value;
}

void SFMLText::SetCenterPos(FPosition * value)
{
	SetPos(value->X - (GetWidth() / 2), value->Y - (GetHeight() / 2));
}

FRectangle * SFMLText::GetRectangle()
{
	FRectangle* rec = new FRectangle(GetX(), GetY(), GetHeight(), GetWidth());

	return rec;
}

float SFMLText::GetHeight()
{
	if (size != NULL)
	{
		return size->Height;
	}
	else
	{
		return 0;
	}
}

float SFMLText::GetWidth()
{
	if (size != NULL)
	{
		return size->Width;
	}
	else
	{
		return 0;
	}
}

void SFMLText::SetHeight(float height)
{
	if (size != NULL)
	{
		size->Height = height;
	}
}

void SFMLText::SetWidth(float width)
{
	if (size != NULL)
	{
		size->Width = width;
	}
}

FSize * SFMLText::GetSize()
{
	return size;
}

void SFMLText::SetSize(float height, float width)
{
	if (size != NULL)
	{
		size->Set(height, width);
	}
}

void SFMLText::SetSize(FSize * value)
{
	if (size != NULL)
		delete size;

	size = value;
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

	textFont = font;

	innerImpl->setFont(*sfmlFont->innerImpl);
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

void SFMLText::UpdateInnerImpl()
{
}

