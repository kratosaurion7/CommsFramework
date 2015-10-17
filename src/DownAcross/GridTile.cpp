#include "GridTile.h"



GridTile::GridTile(int number, GameEngine* engine)
{
    this->tileState = Covered;

    char blockName[255];
    sprintf(blockName, "assets/Tile_0%d.png\0", number);

    this->TileSprite = engine->CreateSprite("", blockName);
    
    this->TileSprite->SetScale(0.5);
}

GridTile::~GridTile()
{
}

void GridTile::Update()
{
    BaseActor::Update();

    switch (this->tileState)
    {
        case Covered:
        {
            this->TileSprite->Show(false);
            this->CoveredSprite->Show(true);
            
            break;
        }
        default:
        case Revealed:
        {
            this->TileSprite->Show(true);
            this->CoveredSprite->Show(false);

            break;
        }
    }

    if (this->TileSprite->Clicked())
    {
        if (this->tileState == Covered)
        {
            this->tileState = Revealed;
        }
        else if (this->tileState == Revealed)
        {
            this->tileState = Covered;
        }
            
    }
}
