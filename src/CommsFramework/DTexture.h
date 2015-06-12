#pragma once

#include <SFML\Graphics.hpp>

#include "FSize.h"

#include "BaseTexture.h"

#include <string>

class DTexture : public BaseTexture
{
public:
    DTexture();
    ~DTexture();

	void Load(std::string path);

	virtual FSize* GetSize();

	sf::Texture* innerImpl;
private:
    

	FSize* size;
};

