#pragma once

#include <SDL_events.h>

#include "Vectors.h"

#include "BaseMouse.h"

class SDLMouse : public BaseMouse
{
public:
    SDLMouse();
    ~SDLMouse();

    virtual bool IsClicked();
    virtual bool IsClicked(MouseButtons button);

    virtual Vector2<float> GetMousePosition();

    void HandleEvent(SDL_Event* anEvent);

private:
    float MouseCoordX = 0;
    float MouseCoordY = 0;

    bool leftButtonClicked = false;
    bool rightButtonClicked = false;
    bool middleButtonClicked = false;
    bool fourthButtonClicked = false;
    bool fifthButtonClicked = false;

};

