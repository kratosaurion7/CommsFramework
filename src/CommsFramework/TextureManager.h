#pragma once

#include <string>

#include "PointerList.h"

class BaseTexture;

/*
  TextureManager 
  - Add existing textures
  - Load textures
  - Return existing texture if it exists before loading
*/
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

    void InsertTexture(BaseTexture* newTexture);

    BaseTexture* GetTexture(BaseTexture* checkedTexture);
    BaseTexture* GetTexture(std::string texturePath);

    BaseTexture* FindTexture(std::string textureName);

	void FlushTexture(BaseTexture* texture);

private:

	PointerList<BaseTexture*> TexturesList;
};

