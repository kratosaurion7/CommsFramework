#include "TextureManager.h"

#include "BaseGraphicEngine.h"
#include "BaseTexture.h"
#include "IOUtilities.h"

TextureManager::TextureManager(BaseGraphicEngine* graphicEngine)
{
	EngineRef = graphicEngine;
	TexturesList = PointerList<BaseTexture*>();
}

TextureManager::~TextureManager()
{
	TexturesList.Release();
}

BaseTexture* TextureManager::Create(std::string textureName)
{
	BaseTexture* tex = EngineRef->CreateTextureInstance();

	tex->TextureName = textureName;

	TexturesList.Add(tex);

	return tex;
}

void TextureManager::AddTexture(BaseTexture * addedTexture)
{
    this->TexturesList.Add(addedTexture);
}

BaseTexture* TextureManager::LoadFromDisk(std::string assetPath, std::string textureName)
{
    BaseTexture* tex = EngineRef->TextureRepo->Create(assetPath);

	// If the texture name is a blank string, use the Name part of the filename as texture name
	if (textureName == "")
	{
		tex->TextureName = GetFileName(assetPath);
	}
	else
	{
		tex->TextureName = textureName;
	}

	TexturesList.Add(tex);

	return tex;
}

BaseTexture* TextureManager::GetTexture(std::string textureName)
{
	return TexturesList.Single([textureName](BaseTexture* texture) { return texture->TextureName == textureName; });
}

void TextureManager::FlushTexture(BaseTexture* texture)
{
	TexturesList.RemoveObject(texture);
}
