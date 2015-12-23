#include "SDLGraphicEngine.h"



SDLGraphicEngine::SDLGraphicEngine()
{

}


SDLGraphicEngine::~SDLGraphicEngine()
{
}

void SDLGraphicEngine::Initialize(GraphicEngineInitParams* params)
{
    int res = 0;

    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if (res != 0)
    {
        fprintf(stderr, "Unable to init SDL with error %s\n", SDL_GetError());

        return;
    }

}

void SDLGraphicEngine::AddObject(BaseSprite * obj)
{
}

void SDLGraphicEngine::AddObject(BaseText * obj)
{
}

void SDLGraphicEngine::RemoveObject(DrawObject * obj)
{
}

PointerList<DrawObject*>* SDLGraphicEngine::GetDrawableList()
{
    return nullptr;
}

DrawObject * SDLGraphicEngine::GetObject(std::string identifier)
{
    return nullptr;
}

BaseSprite * SDLGraphicEngine::CreateSprite(std::string identifier)
{
    return nullptr;
}

BaseTexture * SDLGraphicEngine::CreateTexture()
{
    return nullptr;
}

BaseTexture * SDLGraphicEngine::CreateTexture(std::string texturePath)
{
    return nullptr;
}

BaseFont * SDLGraphicEngine::CreateFont()
{
    return nullptr;
}

BaseText * SDLGraphicEngine::CreateText()
{
    return nullptr;
}

int SDLGraphicEngine::GetFramerate()
{
    return 0;
}

void SDLGraphicEngine::SetFramerate(int framerate)
{
}

void SDLGraphicEngine::SetAutoManagedFramerate(bool isSet)
{
}

void SDLGraphicEngine::SetBackgroundColor(uint32_t color)
{
}

void SDLGraphicEngine::SetBackgroundTexture(BaseTexture * texture)
{
}

void SDLGraphicEngine::Start()
{
}

void SDLGraphicEngine::Draw()
{
}

void SDLGraphicEngine::ProcessEvents()
{
}

void SDLGraphicEngine::Stop()
{
}

bool SDLGraphicEngine::IsRunning()
{
    return false;
}

void SDLGraphicEngine::ReorderSpritesByZIndex()
{
}

void SDLGraphicEngine::FlagForZIndexSorting()
{
}

void SDLGraphicEngine::ReorderSprite(DrawObject * first, DrawObject * second)
{
}
