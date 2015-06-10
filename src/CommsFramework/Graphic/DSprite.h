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

    void SetX();
    void SetY();

    FPosition* GetPos();
    void SetPos(float x, float y);
    

    float GetHeight();
    float GetWidth();

    void SetHeight(float height);
    void SetWidth(float width);

    FSize* GetSize();
    void SetSize(float height, float width);

private:
    sf::Sprite* _innerImpl;

    FPosition* position;
};

