#include "SDLGraphicEngine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifdef WIN32
#include <Windows.h>


#undef CreateFont // Used to hide the Windows implementation of CreateFont since I use a function with that name already.
#endif

#include "GameEngine.h"
#include "TextureManager.h"
#include "DrawObject.h"
#include "GraphicEngineInitParams.h"
#include "BaseSprite.h"
#include "BaseText.h"
#include "BaseTexture.h"
#include "Utilities.h"
#include "Spritesheet.h"
#include "Viewport.h"
#include "Primitives.h"
#include "BitHelper.h"

#include "SDLDrawable.h"
#include "SDLSprite.h"
#include "SDLTexture.h"
#include "SDLText.h"
#include "SDLFont.h"
#include "SDLUtilities.h"


SDLGraphicEngine::SDLGraphicEngine()
{
    mainWindow = NULL;
    TextureRepo = new TextureManager(this);
    Viewport = new ViewportRect();
    drawables = new PointerList<DrawObject*>();
    Spritesheets = new PointerList<Spritesheet*>();
    gameRenderer = NULL;
    WantedFrameRate = 60;
    backgroundSprite = NULL;
    PreviousFrameTick = 0;
    CurrentFrameTick = 0;
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

#ifdef WIN32
    // This section is used to init OS specific options
    InitWin32();

#endif

    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to init SDL with error %s\n", errorString);

        return;
    }

    mainWindow = SDL_CreateWindow(params->WindowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, params->WindowSize->Width * RenderingScaleX, params->WindowSize->Height * RenderingScaleY, 0);

    if (mainWindow == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the window SDL with error %s\n", errorString);

        return;
    }

    Viewport->Width = params->WindowSize->Width * RenderingScaleX;
    Viewport->Height = params->WindowSize->Height * RenderingScaleY;

    gameRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gameRenderer == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the Accelerated Renderer with error %s\n", errorString);

        return;
    }

    res = IMG_Init(IMG_INIT_PNG);

    if (res == 0)
    {
        errorString = IMG_GetError();
        fprintf(stderr, "Unable to create the load SDL_Image with error %s\n", errorString);

        return;
    }

    res = SDL_RenderSetScale(gameRenderer, RenderingScaleX, RenderingScaleY);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to scale by %f,%f with error %s\n", RenderingScaleX, RenderingScaleY, errorString);

        return;
    }

    res = TTF_Init();

    if(res != 0)
    {
        errorString = TTF_GetError();
        fprintf(stderr, "Unable to init SDL_TTF with error %s\n", errorString);
        
        return;
    }

    SetupBackground();

    SDL_ShowWindow(mainWindow);

    engineValid = true;
}

void SDLGraphicEngine::AddObject(BaseSprite* obj)
{
    drawables->Add(obj);

    zIndexNeedsReordering = true;
}

void SDLGraphicEngine::AddObject(BaseText* obj)
{
    drawables->Add(obj);

    zIndexNeedsReordering = true;
}

void SDLGraphicEngine::RemoveObject(DrawObject * obj)
{
    drawables->RemoveObject(obj);
}

void SDLGraphicEngine::AddSpritesheet(Spritesheet* spritesheet)
{
    this->Spritesheets->Add(spritesheet);

    PointerList<BaseTexture*>* extractedSprites = spritesheet->ExtractTextures();

    auto it = ITBEGIN(extractedSprites);
    while (it != ITEND(extractedSprites))
    {
        BaseTexture* tex = *it;
        
        this->TextureRepo->AddTexture(tex);

        it++;
    }

    delete(extractedSprites);
}

PointerList<DrawObject*>* SDLGraphicEngine::GetDrawableList()
{
    return drawables;
}

DrawObject* SDLGraphicEngine::GetDrawableObject(std::string identifier)
{
    // TODO : Implement in base class.
    std::list<DrawObject*>::iterator iter = drawables->GetContainer()->begin();

    while (iter != drawables->GetContainer()->end())
    {
        DrawObject* targetSprite = (*iter);

        if (strcmp(targetSprite->Ident.c_str(), identifier.c_str()) == 0)
        {
            return targetSprite;
        }

        iter++;
    }

    return NULL;
}

BaseSprite* SDLGraphicEngine::CreateSpriteInstance()
{
    SDLSprite* spr = new SDLSprite();
    spr->Engine = this;

    return spr;
}

BaseTexture* SDLGraphicEngine::CreateTextureInstance()
{
    SDLTexture* tex = new SDLTexture();
    tex->Engine = this;
    tex->Graphics = this;

    return tex;
}

BaseFont* SDLGraphicEngine::CreateFontInstance()
{
    BaseFont* font = new SDLFont();

    return font;
}

BaseText* SDLGraphicEngine::CreateTextInstance()
{
    SDLText* text = new SDLText();
    text->Engine = this;

    return text;
}

void SDLGraphicEngine::ReloadSpriteTextures()
{
    auto it = ITBEGIN(this->drawables);
    while (it != ITEND(this->drawables))
    {
        DrawObject* drawable = *it;

        SDLSprite* sprt = dynamic_cast<SDLSprite*>(drawable);

        if (sprt != NULL)
        {
            sprt->Reload();
        }

    }
}

int SDLGraphicEngine::GetFramerate()
{
    return WantedFrameRate;
}

void SDLGraphicEngine::SetFramerate(int framerate)
{
    WantedFrameRate = framerate;
}

void SDLGraphicEngine::SetAutoManagedFramerate(bool isSet)
{
}

void SDLGraphicEngine::SetBackgroundColor(uint32_t color)
{
    // TODO : Implementation doesn't work correctly.

    //rgb(149, 237, 255)
    bg_r = (color & 0x00FF0000) >> 16;
    bg_g = (color & 0x0000FF00) >> 8;
    bg_b = (color & 0x000000FF);
    bg_a = 255;// = (color & 0xFF000000) >> 24;
}

void SDLGraphicEngine::SetBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    bg_r = r;
    bg_g = g;
    bg_b = b;
    bg_a = a;

    backgroundSprite->SetTexture(NULL);
    backgroundSprite->Show(false);
}

void SDLGraphicEngine::SetBackgroundTexture(BaseTexture* texture)
{
    backgroundSprite->SetTexture(texture);
    backgroundSprite->Show(true);
}

void SDLGraphicEngine::Scale(float scaleFactor)
{
    DiagonalDPI = 96 / scaleFactor;
    HorizontalDPI = 96 / scaleFactor;
    VerticalDPI = 96 / scaleFactor;

    SDL_RenderSetScale(this->gameRenderer, DiagonalDPI, DiagonalDPI);
}

void SDLGraphicEngine::Start()
{
    RunEngine = true;
}

void SDLGraphicEngine::Draw()
{
    ProcessDraw(mainWindow);
}

void SDLGraphicEngine::ProcessEvents()
{
    ProcessEvents(mainWindow);
}

void SDLGraphicEngine::Stop()
{
    RunEngine = false;
}

bool SDLGraphicEngine::IsRunning()
{
    return RunEngine;
}

void SDLGraphicEngine::ReorderSpritesByZIndex()
{
    // TODO : Implement in base class
    auto spritesStart = this->drawables->GetContainer()->begin();
    auto spritesEnd = this->drawables->GetContainer()->end();

    drawables->GetContainer()->sort([](DrawObject* a, DrawObject* b) {
        return b->GetZIndex() > a->GetZIndex();
    });

    this->zIndexNeedsReordering = false;
}

void SDLGraphicEngine::FlagForZIndexSorting()
{
    // TODO : Implement in base class
    zIndexNeedsReordering = true;
}

void SDLGraphicEngine::ReorderSprite(DrawObject* first, DrawObject* second)
{
    // TODO : Implement in base class
    std::list<DrawObject*>* spriteslist = this->drawables->GetContainer();
    bool foundFirst = false;
    bool foundSecond = false;
    std::list<DrawObject*>::iterator iterFirst;
    std::list<DrawObject*>::iterator iterSecond;

    int loops = 0;

    auto it = spriteslist->begin();
    while (it != spriteslist->end())
    {
        DrawObject* iter = (*it);

        if (iter == first)
        {
            iterFirst = it;
            foundFirst = true;
        }
        else if (iter == second)
        {
            iterSecond = it;
            foundSecond = true;
        }

        if (foundFirst && foundSecond) // Early break
            break;

        it++;
        loops++;
    }

    if (foundFirst && foundSecond)
    {
        spriteslist->erase(iterSecond);

        spriteslist->insert(iterFirst, second);
    }

}

void SDLGraphicEngine::ProcessDraw(SDL_Window* targetWindow)
{
    CurrentFrameTick = GetTicks();

    if (IsTimeForFrame() && RunEngine)
    {
        SDL_SetRenderDrawColor(gameRenderer, bg_r, bg_g, bg_b, bg_a);

        SDL_RenderClear(gameRenderer); // First step

        auto iter = this->drawables->GetContainer()->begin();
        while (iter != this->drawables->GetContainer()->end())
        {
            DrawObject* target = (*iter);

            if (target->IsVisible())
            {
                SDLDrawable* drawImpl = dynamic_cast<SDLDrawable*>(target);

                if (target->Ident == "ButtonTest")
                {
                    int i = 0;
                }

                if (drawImpl != NULL)
                {
                    SDL_Rect destinationRect = this->GetSpriteRect(target);
                    SDL_Texture* tex = drawImpl->GetDrawableTexture();

                    if (target->Coordinate == DrawObject::VIEWPORT_RELATIVE)
                    {
                        destinationRect.x -= Viewport->X;
                        destinationRect.y -= Viewport->Y;
                    }

                    if (tex == NULL)
                    {
                        tex = SDLTexture::GetMissingTextureTexture(this);
                        destinationRect.w = target->GetWidth();
                        destinationRect.h = target->GetHeight();

                        // If the width or height is 0 nothing will be shown, this will set it do some default values
                        // This is done to clearly mark the texture as missing
                        if (destinationRect.h == 0 || destinationRect.w == 0)
                        {
                            destinationRect.w = 25;
                            destinationRect.h = 25;
                        }
                    }

                    SDL_RenderCopy(gameRenderer, tex, NULL, &destinationRect);
                }
            }

            iter++;
        }

		auto primitiveDrawListPointer = &(this->PrimitiveDrawables);

		auto primitiveIter = ITBEGIN(primitiveDrawListPointer);
		while (primitiveIter != ITEND(primitiveDrawListPointer))
		{
			PrimitiveDrawInfo* nextPrimitive = *primitiveIter;

			this->DrawPrimitive(nextPrimitive);

			primitiveIter++;
		}

		this->PrimitiveDrawables.Release();

        SDL_RenderPresent(gameRenderer); // Final step

        PreviousFrameTick = CurrentFrameTick;
    }
}

void SDLGraphicEngine::ProcessEvents(SDL_Window* targetWindow)
{
    SDL_Event procEvent;

    while (SDL_PollEvent(&procEvent))
    {
        switch (procEvent.type)
        {
            case SDL_WINDOWEVENT:
            {
                break;
            }

            default:
                break;
        }
    }
}

SDL_Rect SDLGraphicEngine::GetSpriteRect(DrawObject* object)
{
    SDL_Rect rec;
    rec.h = object->GetHeight();
    rec.w = object->GetWidth();
    rec.x = object->GetOffsetPos().X;
    rec.y = object->GetOffsetPos().Y;

    return rec;
}

void SDLGraphicEngine::DrawPrimitive(PrimitiveDrawInfo* primitive)
{
	unsigned char* colors = IntToBytes(primitive->Color);
	SDL_SetRenderDrawColor(gameRenderer, colors[0], colors[1], colors[2], colors[3]);

	switch (primitive->CallType)
	{
		case DrawType_Line:
		{
			PrimitiveLineDraw* prim = (PrimitiveLineDraw*)primitive->DrawData;

			SDL_RenderDrawLine(gameRenderer, prim->xA, prim->yB, prim->xB, prim->yB);

			break;
		}
		case DrawType_LineList:
		{
			break;
		}
		case DrawType_Rect:
		{
			PrimitiveRectDraw* prim = (PrimitiveRectDraw*)primitive->DrawData;

			SDL_Rect rec;
			rec.x = prim->x;
			rec.y = prim->y;
			rec.h = prim->h;
			rec.w = prim->w;

			SDL_RenderFillRect(gameRenderer, &rec);

			break;
		}
		default:
			break;
		}

}

bool SDLGraphicEngine::IsTimeForFrame()
{
    int ticks = GetTicks();

    return this->PreviousFrameTick + (1000 / WantedFrameRate) <= ticks;

    //return this->PreviousFrameTick + (1000 / WantedFrameRate) <= this->CurrentFrameTick;
}

void SDLGraphicEngine::SetupBackground()
{
    backgroundSprite = new SDLSprite();

    backgroundSprite->SetZIndex(PRIO::BACKGROUND);
    backgroundSprite->Engine = this;
}

#ifdef WIN32
void SDLGraphicEngine::InitWin32()
{
    SetupDPI();
}

void SDLGraphicEngine::SetupDPI()
{
    HDC deviceContext = GetDC(NULL);

    int dpiX = GetDeviceCaps(deviceContext, LOGPIXELSX);
    int dpiY = GetDeviceCaps(deviceContext, LOGPIXELSY);

    this->RenderingScaleX = dpiX / 96;
    this->RenderingScaleY = dpiY / 96;

    ReleaseDC(NULL, deviceContext);
}

#endif
