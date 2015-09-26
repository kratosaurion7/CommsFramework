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
            bool hasCollision = false;

            auto it2 = engine->GameSprites->GetContainer()->begin();
            while (it2 != engine->GameSprites->GetContainer()->end())
            {
                BaseSprite* otherSprite = (*it2);

                if (sprt != otherSprite)
                {
                    if (sprt->CollisionWith(otherSprite))
                    {
                        hasCollision = true;
                        break;
                    }
                }

                it2++;
            }

            // Need to check collisions for bottom only
            if (!hasCollision)
            {
                sprt->IncrementY(1); // TODO : Get gravity direction and velocity
            }
        }

        it++;
    }
}
