#include "TextureRepository.h"



TextureRepository::TextureRepository(GraphicEngine* engine)
{
    this->Graphics = engine;
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
        loadedTexture = this->Graphics->CreateTexture(texturePath);

        this->loadedTextures->Add(loadedTexture);
    }

    return loadedTexture;
}

BaseTexture* TextureRepository::GetLoadedTexture(std::string path)
{
    auto it = loadedTextures->GetContainer()->begin();
    while (it != loadedTextures->GetContainer()->end())
    {
        BaseTexture* tex = (*it);

        if (tex->TexturePath.compare(path) == 0)
            return tex;
    }

    return NULL;
}
