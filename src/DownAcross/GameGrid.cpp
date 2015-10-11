#include "GameGrid.h"

GameGrid::GameGrid(int squareSize)
{
    Sprites = new PointerList<BaseSprite*>();

    this->SquareSize = squareSize;
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
            std::string elementName = "Block_";
            elementName.append(std::to_string(j));
            elementName.append("_");
            elementName.append(std::to_string(i));

            BaseSprite* gridElement = this->Engine->CreateSprite(elementName);
            this->Sprites->Add(gridElement);

            gridElement->SetTexture(blockTexture);

            gridElement->SetPos(j * BlockSize + (j * SpaceSize), i * BlockSize + (i * SpaceSize));
        }
    }

}
