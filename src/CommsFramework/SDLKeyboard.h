#pragma once

#include <SDL_events.h>
#include <SDL_scancode.h>

#include "PointerList.h"
#include "Pair.h"

#include "BaseKeyboard.h"

class SDLKeyboard : public BaseKeyboard
{
public:
    SDLKeyboard();
    ~SDLKeyboard();

    virtual bool IsKeyPressed(Key key);

    virtual bool IsKeyClicked(Key key);

    virtual void UpdateKeyboardPastState();

    void HandleEvent(SDL_Event* anEvent);

private:
    PointerList<Pair<Key, SDL_Scancode>*>* sdlScanCodesMap;

    BaseList<SDL_Scancode>* currentKeyboardState;
    BaseList<SDL_Scancode>* previousKeyboardState;
};

