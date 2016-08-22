#include "TextureRepository.h"

#include "BaseGraphicEngine.h"
#include "PointerList.h"
#include "BaseTexture.h"


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

BaseTexture* TextureRepository::LoadTexture(std::string texturePath)
{
    BaseTexture* loadedTexture = GetLoadedTexture(texturePath);

    if (loadedTexture == NULL)
    {
        loadedTexture = this->Graphics->CreateTexture();
        int res = loadedTexture->Load(texturePath);

        if (res != 0)
            return NULL; // Texture was not loaded

        this->loadedTextures->Add(loadedTexture);
    }

    return loadedTexture;
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
