#include "TextureManager.h"

#include "BaseGraphicEngine.h"
#include "BaseTexture.h"
#include "IOUtilities.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	TexturesList.Release();
}

void TextureManager::InsertTexture(BaseTexture * newTexture)
{
    TexturesList.Add(newTexture);
}

BaseTexture* TextureManager::GetTexture(BaseTexture * checkedTexture)
{
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

BaseTexture* TextureManager::GetTexture(std::string texturePath)
{
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

BaseTexture* TextureManager::FindTexture(std::string textureName)
{
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
	TexturesList.RemoveObject(texture);
}
