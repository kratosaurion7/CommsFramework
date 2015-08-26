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

void SpriteAnimation::LoadAllResources()
{
    auto it = this->AnimationResources->GetContainer()->begin();
    while (it != this->AnimationResources->GetContainer()->end())
    {
        Resource* res = *it;
        

        it++;
    }
}
