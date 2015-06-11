#pragma once

#include <string.h>

#include <SFML\Graphics.hpp>

#include "DTexture.h"
#include "FPosition.h"
#include "FSize.h"

class DSprite
{
public:
    DSprite();
    ~DSprite();

	std::string* Ident;
	
	virtual void Show(bool show);

	virtual DTexture* GetTexture();
	virtual void SetTexture(DTexture* texture);

    virtual float GetX();
	virtual float GetY();

	virtual void SetX(float value);
	virtual void SetY(float value);

	virtual FPosition* GetPos();
	virtual void SetPos(float x, float y);
	virtual void SetPos(FPosition* value);
    

	virtual float GetHeight();
	virtual float GetWidth();

	virtual void SetHeight(float height);
	virtual void SetWidth(float width);

	virtual FSize* GetSize();
	virtual void SetSize(float height, float width);
	virtual void SetSize(FSize* value);

	sf::Sprite* innerImpl;

private:
    

	DTexture* spriteTexture;

	bool isVisible;

    FPosition* position;
	FSize* size;
};

