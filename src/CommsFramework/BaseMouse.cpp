#include "BaseMouse.h"

bool BaseMouse::LeftButtonClicked()
{
    return this->IsClicked(LEFT);
}

bool BaseMouse::RightButtonClicked()
{
    return this->IsClicked(RIGHT);
}
