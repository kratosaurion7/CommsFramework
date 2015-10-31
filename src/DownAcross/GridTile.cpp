#include "GridTile.h"



GridTile::GridTile(int number, GameEngine* engine)
{
    this->tileState = Covered;
    //this->tileState = Revealed;

    this->tileNumber = number;

    this->Engine = engine;

    char blockName[255];
    sprintf(blockName, "assets/Tile_0%d.png\0", number);

    this->TileSprite = engine->CreateSprite("", blockName);
    this->TileSprite->SetScale(0.5);
    this->Sprites->Add(TileSprite);

    // TODO : Find that texture from somewhere
    BaseTexture* blockTexture = engine->Graphics->CreateTexture();
    blockTexture->Initalize(64, 64);
    blockTexture->SetSolidColor(0xed6495FF);

    this->CoveredSprite = engine->CreateSprite("Covered_Tile");
    this->CoveredSprite->SetTexture(blockTexture);
    this->Sprites->Add(this->CoveredSprite);
}

GridTile::~GridTile()
{
}

void GridTile::SetNewNumber(int newNumber)
{
    char blockName[255];
    sprintf(blockName, "assets/Tile_0%d.png\0", newNumber);

    BaseTexture* oldTexture = this->TileSprite->GetCurrentTexture();

    BaseTexture* newTex = this->Engine->Graphics->CreateTexture();
    newTex->Load(blockName);
    this->TileSprite->SetTexture(newTex);

    delete(oldTexture);

    this->tileNumber = newNumber;
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

    if (this->CoveredSprite->Clicked())
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
