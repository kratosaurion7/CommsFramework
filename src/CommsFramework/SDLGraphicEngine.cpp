#include "SDLGraphicEngine.h"

#include <SDL.h>

#include "TextureRepository.h"
#include "DrawObject.h"
#include "GraphicEngineInitParams.h"
#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseTexture.h"

#include "SDLSprite.h"
#include "SDLTexture.h"

SDLGraphicEngine::SDLGraphicEngine()
{
    mainWindow = NULL;
    TextureRepo = new TextureRepository(this);
    drawables = new PointerList<DrawObject*>();
    gameRenderer = NULL;
}


SDLGraphicEngine::~SDLGraphicEngine()
{
    if (mainWindow != NULL)
        SDL_DestroyWindow(mainWindow);

    if (gameRenderer != NULL)
        SDL_DestroyRenderer(gameRenderer);

    SDL_Quit();
}

void SDLGraphicEngine::Initialize(GraphicEngineInitParams* params)
{
    startParams = params;

    int res = 0;
    const char* errorString;

    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to init SDL with error %s\n", errorString);

        return;
    }

    mainWindow = SDL_CreateWindow(params->WindowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, params->WindowSize->Width, params->WindowSize->Height, 0);

    if (mainWindow == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the window SDL with error %s\n", errorString);

        return;
    }

    gameRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gameRenderer == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the Accelerated Renderer with error %s\n", errorString);

        return;
    }

    SDL_ShowWindow(mainWindow);

    engineValid = true;
}

void SDLGraphicEngine::AddObject(BaseSprite* obj)
{
    drawables->Add(obj);

    //SDLSprite* spr = dynamic_cast<SDLSprite*>(obj);

    //if (spr != NULL)
    //{
    //    this->zIndexNeedsReordering = true;

    //    drawables->Add(spr);
    //}
}

void SDLGraphicEngine::AddObject(BaseText* obj)
{
}

void SDLGraphicEngine::RemoveObject(DrawObject * obj)
{
    drawables->RemoveObject(obj);
}

PointerList<DrawObject*>* SDLGraphicEngine::GetDrawableList()
{
    return drawables;
}

DrawObject* SDLGraphicEngine::GetObject(std::string identifier)
{
    return nullptr;
}

BaseSprite* SDLGraphicEngine::CreateSprite(std::string identifier)
{
    SDLSprite* spr = new SDLSprite();
    spr->Engine = this;
    spr->Ident = identifier;

    return spr;
}

BaseTexture* SDLGraphicEngine::CreateTexture()
{
    SDLTexture* tex = new SDLTexture();
    
    return tex;
}

BaseTexture* SDLGraphicEngine::CreateTexture(std::string texturePath)
{
    BaseTexture* tex = this->TextureRepo->LoadTexture(texturePath);

    return tex;
}

BaseFont* SDLGraphicEngine::CreateFont()
{
    return nullptr;
}

BaseText* SDLGraphicEngine::CreateText()
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

void SDLGraphicEngine::ReorderSprite(DrawObject* first, DrawObject* second)
{
}