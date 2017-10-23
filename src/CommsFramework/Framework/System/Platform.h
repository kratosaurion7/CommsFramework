#pragma once

#ifdef WIN32

#define SUPPORT_SDL 1
#define SUPPORT_DIRECTX 1
#define SUPPORT_OPENGL 1

#define SUPPORT_DIRECTINPUT 1

#elif linux

#define SUPPORT_SDL 1
#define SUPPORT_DIRECTX 0
#define SUPPORT_OPENGL 1

#define SUPPORT_DIRECTINPUT 0

#elif __EMSCRIPTEN__

#define SUPPORT_SDL 1
#define SUPPORT_DIRECTX 0
#define SUPPORT_OPENGL 0

#define SUPPORT_DIRECTINPUT 0

#endif

class BaseMouse;
class BaseKeyboard;
class BaseGraphicEngine;

enum AvailableGraphicEngines
{
    GFXNONE = -1,
    SDL2GFX,
    DIRECTX,
    OPENGL
};

enum AvailableInputLibraries
{
    INPUTNONE = -1,
    SDL2INPUT,
    DIRECTINPUT
};

class Platform
{
public:
    static BaseMouse* CreateDefaultPlatformMouse();
    static BaseKeyboard* CreateDefaultPlatformKeyboard();
    static BaseGraphicEngine* CreateDefaultPlatformGraphicEngine();
    
    static BaseMouse* CreatePlatformMouse(enum AvailableInputLibraries choice);
    static BaseKeyboard* CreatePlatformKeyboard(enum AvailableInputLibraries choice);
    static BaseGraphicEngine* CreatePlatformGraphicEngine(enum AvailableGraphicEngines choice);

    static void ExecutePlatformEvents(BaseGraphicEngine* engine, BaseMouse* mouse, BaseKeyboard* keyboard);
    
private:
    static enum AvailableGraphicEngines CurrentGraphicEngine;
    static enum AvailableInputLibraries CurrentInputLibrary;
    
    
};

