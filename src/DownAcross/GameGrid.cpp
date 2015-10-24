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

    Tiles->Release();
    delete(Tiles);

    InfoTiles->Release();
    delete(InfoTiles);
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
            GridTile* newTile = new GridTile(this->Engine->Rng->GetRandom(10), this->Engine);

            newTile->MoveTo(j * BlockSize + (j * SpaceSize), i * BlockSize + (i * SpaceSize));

            this->Tiles->Add(newTile);

            this->Engine->AttachActor(newTile);
        }
    }

    // Placing the InfoTiles for the rows (at the right)
    for (int i = 0; i < SquareSize; i++)
    {
        BaseSprite* rightMostTile = this->Tiles->Get(i * SquareSize + SquareSize - 1)->TileSprite;

        FPosition rightMostPosition = rightMostTile->GetOffsetPos();

        FPosition posOffset = rightMostPosition;
        posOffset.X += rightMostTile->GetWidth() + 10;

        InfoTile* info = new InfoTile(GetZeroesOfRow(i), GetSumOfRow(i), this->Engine);
        InfoTiles->Add(info);
        
        Engine->AttachActor(info);

        //info->BackgroundSprite->SetPos(posOffset);
        info->MoveTo(posOffset.X, posOffset.Y);
    }

    // Placing the InfoTiles for the columns (at the bottom)
    for (int j = 0; j < SquareSize; j++)
    {
        BaseSprite* bottomMostTile = this->Tiles->Get(SquareSize * SquareSize - SquareSize + j)->TileSprite;

        FPosition bottomMostPosition = bottomMostTile->GetOffsetPos();
        
        FPosition posOffset = bottomMostPosition;
        posOffset.Y += bottomMostTile->GetHeight() + 10;

        InfoTile* info = new InfoTile(GetZeroesOfColumn(j), GetSumOfColumn(j), this->Engine);
        InfoTiles->Add(info);
        Engine->AttachActor(info);

        //info->BackgroundSprite->SetPos(posOffset);
        info->MoveTo(posOffset.X, posOffset.Y);
    }
}



void GameGrid::RefreshGridTileInformations()
{
    for (int i = 0; i < 5; i++)
    {
        InfoTile* tile = this->InfoTiles->Get(i);
        tile->nbOfZeroes = this->GetZeroesOfRow(i);
        std::string zeroText = std::to_string(tile->nbOfZeroes);
        tile->nbOfZeroesText->SetText(zeroText);

        tile->sumOfColumnOrRow = this->GetSumOfRow(i);
        std::string sumText = std::to_string(tile->sumOfColumnOrRow);
        tile->sumOfColumnOrRowText->SetText(sumText);

    }

    for (int i = 0; i < 5; i++)
    {
        InfoTile* tile = this->InfoTiles->Get(i+5);
        tile->nbOfZeroes = this->GetZeroesOfColumn(i);
        std::string zeroText = std::to_string(tile->nbOfZeroes);
        tile->nbOfZeroesText->SetText(zeroText);

        tile->sumOfColumnOrRow = this->GetSumOfColumn(i);
        std::string sumText = std::to_string(tile->sumOfColumnOrRow);
        tile->sumOfColumnOrRowText->SetText(sumText);
    }

}


void GameGrid::Update()
{
    BaseActor::Update();

    if (this->Engine->Keyboard->IsKeyClicked(Space))
    {
        auto it = this->Tiles->GetContainer()->begin();
        while (it != this->Tiles->GetContainer()->end())
        {
            GridTile* tile = (*it);

            int newNumber = this->Engine->Rng->GetRandom(10);

            tile->SetNewNumber(newNumber);

            it++;
        }

        this->RefreshGridTileInformations();
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
