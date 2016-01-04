#include "SDLMouse.h"


SDLMouse::SDLMouse()
{
}


SDLMouse::~SDLMouse()
{
}

bool SDLMouse::IsClicked()
{
    return this->leftButtonClicked ||
        this->rightButtonClicked ||
        this->middleButtonClicked ||
        this->fourthButtonClicked ||
        this->fifthButtonClicked;
}

bool SDLMouse::IsClicked(MouseButtons button)
{
    switch (button)
    {
        case LEFT:
            return this->leftButtonClicked;
            break;
        case RIGHT:
            return this->rightButtonClicked;
            break;
        case MIDDLE:
            return this->middleButtonClicked;
            break;
        case BUTTON3:
            return this->fourthButtonClicked;
            break;
        case BUTTON4:
            return this->fifthButtonClicked;
            break;
        default:
            return false;
            break;
    }
}

Vector2<float> SDLMouse::GetMousePosition()
{
    Vector2<float> pos;
    pos.X = MouseCoordX;
    pos.Y = MouseCoordY;

    return pos;
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
