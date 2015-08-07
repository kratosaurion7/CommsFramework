#pragma once

#include <SFML\Graphics.hpp>

#include "FSize.h"

#include "BaseTexture.h"

#include <string>

#include <cstdint>

class DTexture : public BaseTexture
{
public:
    DTexture();
    ~DTexture();

	virtual void Initalize(int width, int height);

	void Load(std::string path);

    virtual void LoadFromMemory(char* data, int dataSize);

	virtual FSize* GetSize();

    

	virtual void SetSolidColor(uint32_t pixelColor);

	sf::Texture* innerImpl;

private:
	FSize* size;

};

