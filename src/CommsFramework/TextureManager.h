#pragma once

#include <string>

#include "PointerList.h"

class BaseGraphicEngine;
class BaseTexture;

class TextureManager
{
public:
	TextureManager(BaseGraphicEngine* graphicEngine);
	~TextureManager();

	BaseTexture* Create(std::string textureName);

    void AddTexture(BaseTexture* addedTexture);

	BaseTexture* LoadFromDisk(std::string assetPath, std::string textureName = "");

	BaseTexture* GetTexture(std::string textureName);

	void FlushTexture(BaseTexture* texture);

private:
	BaseGraphicEngine* EngineRef;

	PointerList<BaseTexture*> TexturesList;
};

