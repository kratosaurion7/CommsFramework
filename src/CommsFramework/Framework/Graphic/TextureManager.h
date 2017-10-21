#pragma once

#include <string>

#include "Collections/PointerList.h"

class BaseTexture;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

    void InsertTexture(BaseTexture* newTexture);

    BaseTexture* GetTexture(BaseTexture* checkedTexture);
    BaseTexture* GetTextureByPath(std::string texturePath);
    BaseTexture* GetTextureByName(std::string textureName);

	void FlushTexture(BaseTexture* texture);

private:

	PointerList<BaseTexture*> TexturesList;
};

