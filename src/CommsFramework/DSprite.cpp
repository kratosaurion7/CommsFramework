#include "DSprite.h"

#include <SFML\Graphics.hpp>

DSprite::DSprite()
{
	innerImpl = new sf::Sprite();
	spriteTexture = NULL;
	isVisible = true;
	position = new FPosition();
	size = new FSize();
}

DSprite::~DSprite()
{
	// Don't delete the sprite texture when deleting a sprite, the texture might be shared around.
	delete innerImpl;
	delete position;
	delete size;
}

void DSprite::Show(bool show)
{
	isVisible = show;
}

DTexture* DSprite::GetTexture()
{
	return spriteTexture;
}

// TODO : Need to receive a BaseTexture but it always(?) is going to be a DTexture anyway
//void DSprite::SetTexture(DTexture * texture)
void DSprite::SetTexture(BaseTexture * texture)
{
	DTexture* dtxr = dynamic_cast<DTexture*>(texture);

	if (dtxr != NULL)
	{
		innerImpl->setTexture((*dtxr->innerImpl));
		spriteTexture = dtxr;
		size = texture->GetSize();
	}
		
}

float DSprite::GetX()
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

float DSprite::GetY()
{
	if(position != NULL)
	{
		return position->Y;
	}
	else
	{
		return 0;
	}
}

void DSprite::SetX(float value)
{
	if (position != NULL)
	{
		position->X = value;

		UpdateInnerImpl();
	}
}

void DSprite::SetY(float value)
{
	if (position != NULL)
	{
		position->Y = value;

		UpdateInnerImpl();
	}
}

void DSprite::IncrementX(float value)
{
	position->X += value;

	UpdateInnerImpl();
}

void DSprite::IncrementY(float value)
{
	position->Y += value;

	UpdateInnerImpl();
}

FPosition* DSprite::GetPos()
{
	return position;
}

void DSprite::SetPos(float x, float y)
{
	if (position != NULL)
		delete position;

	position = new FPosition(x, y);
	
	UpdateInnerImpl();
}

void DSprite::SetPos(FPosition * value)
{
	if (position != NULL)
		delete position;

	position = value;

	UpdateInnerImpl();
}

float DSprite::GetHeight()
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

float DSprite::GetWidth()
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

void DSprite::SetHeight(float height)
{
	if (size != NULL)
	{
		size->Height = height;
	}
}

void DSprite::SetWidth(float width)
{
	if (size != NULL)
	{
		size->Width = width;
	}
}

FSize* DSprite::GetSize()
{
	return size;
}

void DSprite::SetSize(float height, float width)
{
	if (size != NULL)
		delete size;

	size = new FSize(height, width);
}

void DSprite::SetSize(FSize * value)
{
	if (size != NULL)
		delete size;

	size = value;
}

bool DSprite::IsVisible()
{
	return isVisible;
}

void DSprite::UpdateInnerImpl()
{
	innerImpl->setPosition(position->X, position->Y);
}
