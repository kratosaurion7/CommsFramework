#include "SpriteAnimation.h"



SpriteAnimation::SpriteAnimation()
{
    AnimationResources = new PointerList<Resource*>();
}


SpriteAnimation::~SpriteAnimation()
{
    AnimationResources->Clear();
    delete(AnimationResources);
}
