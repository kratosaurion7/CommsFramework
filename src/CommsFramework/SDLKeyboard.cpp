#include "SDLKeyboard.h"



SDLKeyboard::SDLKeyboard()
{
    sdlScanCodesMap = new PointerList<Pair<Key, SDL_Scancode>*>();

    BuildKeyMap();

    currentKeyboardState = NULL;
    previousKeyboardState = NULL;

}


SDLKeyboard::~SDLKeyboard()
{
    sdlScanCodesMap->Clear();
    delete(sdlScanCodesMap);
}

bool SDLKeyboard::IsKeyPressed(Key key)
{
    return false;

    //const Uint8 *state = SDL_GetKeyboardState(NULL);

    //SDL_Scancode mappedScanCode = sdlScanCodesMap->Single([key](Pair<Key, SDL_Scancode>* pair) { return pair->Item1 == key;})->Item2;

    //return state[mappedScanCode];
}

bool SDLKeyboard::IsKeyClicked(Key key)
{
    auto it = sdlScanCodesMap->GetContainer()->begin();
    while (it != sdlScanCodesMap->GetContainer()->end())
    {
        Pair<Key, SDL_Scancode>* keyMap = (*it);

        if (keyMap->Item1 == key)
        {
            return currentKeyboardState[keyMap->Item2];
        }


        it++;
    }
}

void SDLKeyboard::UpdateKeyboardState()
{
    currentKeyboardState = SDL_GetKeyboardState(NULL);
}

void SDLKeyboard::UpdateKeyboardPastState()
{
    previousKeyboardState = currentKeyboardState;
}

void SDLKeyboard::HandleEvent(SDL_Event* anEvent)
{
    switch (anEvent->type)
    {
        case SDL_KEYDOWN: // Key states are retrieved dynamically in the IsKeyPressed function
        case SDL_KEYUP:
            break;

        default:
            break;
    }
}

void SDLKeyboard::BuildKeyMap()
{
}
