#include "Platform.h"


#if SUPPORT_SDL == 1

#include <SDL_events.h>

#include "Graphic/SDL/SDLMouse.h"
#include "Graphic/SDL/SDLKeyboard.h"
#include "Graphic/SDL/SDLGraphicEngine.h"

#endif

#if SUPPORT_DIRECTX == 1

#include "Graphic/DX2D/DX2DMouse.h"
#include "Graphic/DX2D/DX2DKeyboard.h"
#include "Graphic/DX2D/DX2DGraphicEngine.h"

#endif

#if SUPPORT_OPENGL == 1
#endif

#if SUPPORT_DIRECTINPUT == 1
#endif

enum AvailableGraphicEngines Platform::CurrentGraphicEngine = GFXNONE;
enum AvailableInputLibraries Platform::CurrentInputLibrary = INPUTNONE;

BaseMouse* Platform::CreateDefaultPlatformMouse()
{
#ifdef WIN32
    CurrentInputLibrary = SDL2INPUT;

    return new SDLMouse();
    
#elif linux
    CurrentInputLibrary = SDL2INPUT;

    return new SDLMouse();
    
#elif __EMSCRIPTEN__
    CurrentInputLibrary = SDL2INPUT;

    return new SDLMouse();
    
#endif
    
    return NULL;
}

BaseKeyboard* Platform::CreateDefaultPlatformKeyboard()
{
#ifdef WIN32
    CurrentInputLibrary = SDL2INPUT;

    return new SDLKeyboard();
    
#elif linux
    CurrentInputLibrary = SDL2INPUT;

    return new SDLKeyboard();
    
#elif __EMSCRIPTEN__
    CurrentInputLibrary = SDL2INPUT;

    return new SDLKeyboard();
    
#endif
    
    return NULL;
}

BaseGraphicEngine* Platform::CreateDefaultPlatformGraphicEngine()
{
#ifdef WIN32
    CurrentGraphicEngine = SDL2GFX;

    return new SDLGraphicEngine();
    
#elif linux
    return new SDLGraphicEngine();
    
#elif __EMSCRIPTEN__
    return new SDLGraphicEngine();
    
#endif

    return NULL;
}

BaseMouse* Platform::CreatePlatformMouse(enum AvailableInputLibraries choice)
{
    switch(choice)
    {
#if SUPPORT_SDL == 1
        case SDL2INPUT:
        {
            CurrentInputLibrary = SDL2INPUT;

            return new SDLMouse();
        }
#endif
#if SUPPORT_DIRECTINPUT == 1
        case DIRECTINPUT:
        {
            // Not implemented
            break;
        }
#endif
        default:
        {
            break;
        }
    }
    
    return NULL;
}

BaseKeyboard* Platform::CreatePlatformKeyboard(enum AvailableInputLibraries choice)
{
    switch(choice)
    {
#if SUPPORT_SDL == 1
        case SDL2INPUT:
        {
            CurrentInputLibrary = SDL2INPUT;

            return new SDLKeyboard();
        }
#endif
#if SUPPORT_DIRECTINPUT == 1
        case DIRECTINPUT:
        {
            // Not implemented
            break;
        }
#endif
        default:
        {
            break;
        }
    }
    
    return NULL;
}

BaseGraphicEngine* Platform::CreatePlatformGraphicEngine(enum AvailableGraphicEngines choice)
{
    switch(choice)
    {
#if SUPPORT_SDL == 1
        case SDL2GFX:
        {
            CurrentGraphicEngine = SDL2GFX;

            return new SDLGraphicEngine();
        }
#endif
#if SUPPORT_DIRECTX == 1
        case DIRECTX:
        {
            // Not implemented
            break;
        }
#endif
#if SUPPORT_OPENGL == 1
    case OPENGL:
    {
        // Not implemented
        break;
    }
#endif
        default:
        {
            break;
        }
    }
    
    return NULL;
}

void Platform::ExecutePlatformEvents(BaseGraphicEngine* engine, BaseMouse* mouse, BaseKeyboard* keyboard)
{
    switch (CurrentInputLibrary)
    {
    case INPUTNONE:
        break;
#if SUPPORT_SDL
    case SDL2INPUT:
    {
        SDL_Event myEvent;
        while (SDL_PollEvent(&myEvent)) {
            switch (myEvent.type)
            {
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                ((SDLMouse*)mouse)->HandleEvent(&myEvent);
                break;
            }
            case SDL_QUIT:
            {
                exit(0);

                break;
            }
            case SDL_WINDOWEVENT:
            {
                break;
            }
            default:
                break;
            }
        }

        break;
    }
#endif
#if SUPPORT_DIRECTINPUT
    case DIRECTINPUT:
    {
        DX2DGraphicEngine* eng = (DX2DGraphicEngine*)engine;
        eng->ProcessWindowEvents();

        DX2DMouse* d2Mouse = (DX2DMouse*)mouse;
        d2Mouse->MouseCoordX = eng->MouseX;
        d2Mouse->MouseCoordY = eng->MouseY;
        d2Mouse->Left_Current_State = eng->leftButtonState;
        
        break;
    }
#endif
    default:
        break;
    }
}
