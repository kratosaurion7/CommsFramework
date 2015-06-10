#pragma once

#include <SFML\Graphics.hpp>

#include "FSize.h"

#include <string>

class DTexture
{
public:
    DTexture();
    ~DTexture();

	void Load(std::string path);

	virtual FSize* GetSize();

private:
    sf::Texture* innerImpl;

	FSize* size;
};

