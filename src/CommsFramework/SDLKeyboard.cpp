#include "SDLKeyboard.h"



SDLKeyboard::SDLKeyboard()
{
    sdlScanCodesMap = new PointerList<Pair<Key, SDL_Scancode>*>();

    BuildKeyMap();

    currentKeyboardState = new BaseList<SDL_Scancode>();
    previousKeyboardState = new BaseList<SDL_Scancode>();
}


SDLKeyboard::~SDLKeyboard()
{
    sdlScanCodesMap->Clear();
    delete(sdlScanCodesMap);
}

bool SDLKeyboard::IsKeyPressed(Key key)
{
    return currentKeyboardState->ContainsItem((SDL_Scancode)(key));
}

bool SDLKeyboard::IsKeyClicked(Key key)
{
    return IsKeyPressed(key); // Temporary fix

    bool previous = !currentKeyboardState->ContainsItem((SDL_Scancode)key);
    bool current = currentKeyboardState->ContainsItem((SDL_Scancode)key);

    return previous && current;
}

void SDLKeyboard::UpdateKeyboardPastState()
{
    previousKeyboardState->Clear();
    previousKeyboardState->AddRange(currentKeyboardState);
    currentKeyboardState->Clear();
}

void SDLKeyboard::HandleEvent(SDL_Event* anEvent)
{
    SDL_Scancode x = anEvent->key.keysym.scancode;
    switch (anEvent->type)
    {
        case SDL_KEYDOWN: // Key states are retrieved dynamically in the IsKeyPressed function
            currentKeyboardState->Add(x);
            
            break;
        case SDL_KEYUP:
            //currentKeyboardState->RemoveObject(x);

            break;

        default:
            break;
    }
}

void SDLKeyboard::BuildKeyMap()
{
}
