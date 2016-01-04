#pragma once

#include <SDL_events.h>

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

    virtual void UpdateKeyboardState();

    void HandleEvent(SDL_Event* anEvent);

private:
    PointerList<Pair<Key, SDL_Scancode>*>* sdlScanCodesMap;

    void BuildKeyMap();
};

