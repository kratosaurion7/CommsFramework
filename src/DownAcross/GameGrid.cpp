#include "GameGrid.h"

GameGrid::GameGrid(int squareSize, GameEngine* engine)
{
    Sprites = new PointerList<BaseSprite*>();

    Tiles = new PointerList<GridTile*>();

    this->SquareSize = squareSize;

    this->Engine = engine;
}

GameGrid::~GameGrid()
{
    delete(Sprites);
}

void GameGrid::Setup()
{
    BaseTexture* blockTexture = Engine->Graphics->CreateTexture();
    blockTexture->Initalize(BlockSize, BlockSize);
    blockTexture->SetSolidColor(0xFF0000FF);

    for (int i = 0; i < SquareSize; i++) // Y
    {
        for (int j = 0; j < SquareSize; j++) // X
        {
            GridTile* newTile = new GridTile((i + j) % 10, this->Engine);

            std::string elementName = "Block_";
            elementName.append(std::to_string(j));
            elementName.append("_");
            elementName.append(std::to_string(i));

            BaseSprite* gridElement = this->Engine->CreateSprite(elementName);

            gridElement->SetTexture(blockTexture);

            gridElement->SetPos(j * BlockSize + (j * SpaceSize), i * BlockSize + (i * SpaceSize));

            newTile->CoveredSprite = gridElement;
            newTile->TileSprite->SetPos(j * BlockSize + (j * SpaceSize), i * BlockSize + (i * SpaceSize));
            this->Tiles->Add(newTile);

            this->Engine->AttachActor(newTile);
        }
    }

}