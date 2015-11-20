#pragma once

#include <BaseSprite.h>
#include <BaseActor.h>

class Card : public BaseActor
{
public:
    Card();
    ~Card();

    BaseSprite* cardFront;
    BaseSprite* cardBack;
};