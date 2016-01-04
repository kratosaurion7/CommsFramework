#include "SDLMouse.h"


SDLMouse::SDLMouse()
{
}


SDLMouse::~SDLMouse()
{
}

bool SDLMouse::IsClicked()
{
    return false;
}

bool SDLMouse::IsClicked(MouseButtons button)
{
    return false;
}

Vector2<float> SDLMouse::GetMousePosition()
{
    return Vector2<float>();
}

void SDLMouse::HandleEvent(SDL_Event* anEvent)
{
    // Needed ?
    //leftButtonClicked = false;
    //rightButtonClicked = false;
    //middleButtonClicked = false;
    //fourthButtonClicked = false;
    //fifthButtonClicked = false;

    switch (anEvent->type)
    {
        case SDL_MOUSEMOTION:
        {
            this->MouseCoordX = anEvent->motion.x;
            this->MouseCoordY = anEvent->motion.y;

            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (anEvent->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    this->leftButtonClicked = true;

                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    this->middleButtonClicked = true;
                    
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    this->rightButtonClicked = true;

                    break;
                }
                case SDL_BUTTON_X1:
                {
                    this->fourthButtonClicked = true;

                    break;
                }
                case SDL_BUTTON_X2:
                {
                    this->fifthButtonClicked = true;

                    break;
                }

                default:
                    break;
            }
        }
        case SDL_MOUSEBUTTONUP:
        {
            switch (anEvent->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    this->leftButtonClicked = false;

                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    this->middleButtonClicked = false;

                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    this->rightButtonClicked = false;

                    break;
                }
                case SDL_BUTTON_X1:
                {
                    this->fourthButtonClicked = false;

                    break;
                }
                case SDL_BUTTON_X2:
                {
                    this->fifthButtonClicked = false;

                    break;
                }

                default:
                    break;
            }
        }

        default:
            break;
    }
}
