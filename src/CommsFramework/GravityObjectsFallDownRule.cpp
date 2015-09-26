#include "GravityObjectsFallDownRule.h"

#include "GameRule.h"


GravityObjectsFallDownRule::GravityObjectsFallDownRule() : GameRule("r_gravity")
{
}


GravityObjectsFallDownRule::~GravityObjectsFallDownRule()
{
}

void GravityObjectsFallDownRule::Update(GameEngine * engine)
{
    auto it = engine->GameSprites->GetContainer()->begin();
    while (it != engine->GameSprites->GetContainer()->end())
    {
        BaseSprite* sprt = (*it);

        if (sprt->GravityEnabled)
        {
            sprt->IncrementY(1); // TODO : Get gravity direction and velocity
        }

        it++;
    }
}
