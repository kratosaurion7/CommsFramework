#include "TextureManager.h"

#include "Graphic/Base Classes/BaseGraphicEngine.h"
#include "Graphic/Base Classes/BaseTexture.h"
#include "Filesystem/IOUtilities.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	TexturesList.Release();
}

void TextureManager::InsertTexture(BaseTexture* newTexture)
{
    TexturesList.Add(newTexture);
}

BaseTexture* TextureManager::GetTexture(BaseTexture* checkedTexture)
{
	assert(checkedTexture != NULL);

    auto it = ITBEGIN((&TexturesList));
    while (it != ITEND((&TexturesList)))
    {
        BaseTexture* tex = *it;

        if (tex == checkedTexture)
        {
            return tex;
        }

        it++;
    }

    return NULL;
}

BaseTexture* TextureManager::GetTextureByPath(std::string texturePath)
{
	if (texturePath == "")
		return NULL;

    auto it = ITBEGIN((&TexturesList));
    while (it != ITEND((&TexturesList)))
    {
        BaseTexture* tex = *it;

        if (tex->TexturePath == texturePath)
        {
            return tex;
        }

        it++;
    }

    return NULL;
}

BaseTexture* TextureManager::GetTextureByName(std::string textureName)
{
	if (textureName == "")
		return NULL;

    auto it = ITBEGIN((&TexturesList));
    while (it != ITEND((&TexturesList)))
    {
        BaseTexture* tex = *it;

        if (tex->TextureName == textureName)
        {
            return tex;
        }

        it++;
    }

    return NULL;
}

void TextureManager::FlushTexture(BaseTexture* texture)
{
	assert(texture != NULL);

	TexturesList.RemoveObject(texture);
}
