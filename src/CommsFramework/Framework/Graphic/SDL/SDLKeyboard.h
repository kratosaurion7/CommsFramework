#pragma once

#include <SDL_events.h>
#include <SDL_scancode.h>

#include "Collections/PointerList.h"
#include "Types/Pair.h"

#include "Graphic/Base Classes/BaseKeyboard.h"

class SDLKeyboard : public BaseKeyboard
{
public:
    SDLKeyboard();
    ~SDLKeyboard();

    virtual bool IsKeyPressed(Key key);

    virtual bool IsKeyClicked(Key key);

    virtual void UpdateKeyboardState();

private:
    int keysCount;
    Uint8* previousScancodes;
    const Uint8* currentScancodes;

    PointerList<Pair<Key, SDL_Scancode>*>* sdlScanCodesMap;
};

