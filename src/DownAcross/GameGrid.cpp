#include "GameGrid.h"

GameGrid::GameGrid(int squareSize, GameEngine* engine)
{
    Tiles = new PointerList<GridTile*>();

    InfoTiles = new PointerList<InfoTile*>();

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

    // Placing the InfoTiles for the rows (at the right)
    for (int i = 0; i < SquareSize; i++)
    {
        BaseSprite* rightMostTile = this->Tiles->Get(i * SquareSize + SquareSize - 1)->TileSprite;

        FPosition rightMostPosition = rightMostTile->GetPos();

        FPosition posOffset = rightMostPosition;
        posOffset.X += rightMostTile->GetWidth() + 10;

        InfoTile* info = new InfoTile(GetZeroesOfRow(i), GetSumOfRow(i), this->Engine);
        InfoTiles->Add(info);
        Engine->AttachActor(info);

        info->BackgroundSprite->SetPos(posOffset);
    }

    // Placing the InfoTiles for the columns (at the bottom)
    for (int j = 0; j < SquareSize; j++)
    {
        BaseSprite* bottomMostTile = this->Tiles->Get(SquareSize * SquareSize - SquareSize + j)->TileSprite;

        FPosition bottomMostPosition = bottomMostTile->GetPos();
        
        FPosition posOffset = bottomMostPosition;
        posOffset.Y += bottomMostTile->GetHeight() + 10;

        InfoTile* info = new InfoTile(GetZeroesOfColumn(j), GetSumOfColumn(j), this->Engine);
        InfoTiles->Add(info);
        Engine->AttachActor(info);

        info->BackgroundSprite->SetPos(posOffset);
    }


}

int GameGrid::GetZeroesOfRow(int rowNb)
{
    int zeroesTotal = 0;

    for (int i = 0; i < SquareSize; i++)
    {
        GridTile* rowTile = this->Tiles->Get((SquareSize * rowNb) + i);

        if (rowTile->tileNumber == 0)
            zeroesTotal++;
    }

    return zeroesTotal;
}

int GameGrid::GetSumOfRow(int rowNb)
{
    int sum = 0;

    for (int i = 0; i < SquareSize; i++)
    {
        GridTile* rowTile = this->Tiles->Get((SquareSize * rowNb) + i);

        sum += rowTile->tileNumber;
    }

    return sum;
}

int GameGrid::GetZeroesOfColumn(int colNb)
{
    int zeroesTotal = 0;

    for (int i = 0; i < SquareSize; i++)
    {
        GridTile* columnTile = this->Tiles->Get(i * SquareSize + colNb);

        if (columnTile->tileNumber == 0)
            zeroesTotal++;
    }
    
    return zeroesTotal;
}

int GameGrid::GetSumOfColumn(int colNb)
{
    int sum = 0;

    for (int i = 0; i < SquareSize; i++)
    {
        GridTile* columnTile = this->Tiles->Get(i * SquareSize + colNb);

        sum += columnTile->tileNumber;
    }

    return sum;
}
