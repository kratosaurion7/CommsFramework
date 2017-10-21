#include "TextureRepository.h"

#include "Graphic/Base Classes/BaseGraphicEngine.h"
#include "Graphic/Base Classes/BaseTexture.h"
#include "Collections/PointerList.h"
#include "Filesystem/IOUtilities.h"

TextureRepository::TextureRepository(BaseGraphicEngine* engine)
{
    this->Graphics = engine;

    loadedTextures = new PointerList<BaseTexture*>();
}


TextureRepository::~TextureRepository()
{
    loadedTextures->Release();
    delete(loadedTextures);
}

BaseTexture* TextureRepository::LoadTexture(std::string texturePath, std::string newTextureName)
{
    BaseTexture* loadedTexture = GetLoadedTexture(texturePath);

    if (loadedTexture == NULL)
    {
        loadedTexture = this->Graphics->CreateTextureInstance();
        int res = loadedTexture->Load(texturePath);

        if (res != 0)
            return NULL; // Texture was not loaded

        if (newTextureName == "")
        {
            loadedTexture->TextureName = GetFileName(texturePath);
        }
        else
        {
            loadedTexture->TextureName = newTextureName;
        }


        this->loadedTextures->Add(loadedTexture);
    }

    return loadedTexture;
}

void TextureRepository::FlushTexture(std::string textureName)
{
    BaseTexture* texture = GetTextureByName(textureName);

    if (texture != NULL)
    {
        delete(texture);
    }

    this->loadedTextures->RemoveObject(texture);
}

BaseTexture* TextureRepository::GetTextureByName(std::string textureName)
{
    auto it = loadedTextures->GetContainer()->begin();
    while (it != loadedTextures->GetContainer()->end())
    {
        BaseTexture* tex = (*it);

        if (tex->TextureName.compare(textureName) == 0)
            return tex;

        it++;
    }

    return NULL;
}

BaseTexture* TextureRepository::GetLoadedTexture(std::string path)
{
    auto it = loadedTextures->GetContainer()->begin();
    while (it != loadedTextures->GetContainer()->end())
    {
        BaseTexture* tex = (*it);

        if (tex->TexturePath.compare(path) == 0)
            return tex;

        it++;
    }

    return NULL;
}
