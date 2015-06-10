#pragma once

#include <SFML\Graphics.hpp>

#include "DTexture.h"

#include "FPosition.h"
#include "FSize.h"

class DSprite
{
public:
    DSprite();
    ~DSprite();

    void Show(bool show);

    DTexture* GetTexture();
    void SetTexture(DTexture* texture);


    float GetX();
    float GetY();

    void SetX(float value);
    void SetY(float value);

    FPosition* GetPos();
    void SetPos(float x, float y);
	void SetPos(FPosition* value);
    

    float GetHeight();
    float GetWidth();

    void SetHeight(float height);
    void SetWidth(float width);

    FSize* GetSize();
    void SetSize(float height, float width);
	void SetSize(FSize* value);

private:
    sf::Sprite* innerImpl;

	DTexture* spriteTexture;

	bool isVisible;

    FPosition* position;
	FSize* size;
};

