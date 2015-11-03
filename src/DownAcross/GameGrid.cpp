#include "GameGrid.h"

GameGrid::GameGrid(int squareSize, GameEngine* engine)
{
    Tiles = new PointerList<GridTile*>();

    InfoTiles = new PointerList<InfoTile*>();

    CurrentState = GameGridState::PLAYING;

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
    blockTexture = Engine->Graphics->CreateTexture();
    blockTexture->Initalize(BlockSize, BlockSize);
    blockTexture->SetSolidColor(0xFF0000FF);

    rng = new WeightedNumberGenerator();
    rng->AddBucket(0, 0.20);
    rng->AddBucket(1, 0.75);
    rng->AddBucket(2, 0.05);

    for (int i = 0; i < SquareSize; i++) // Y
    {
        for (int j = 0; j < SquareSize; j++) // X
        {
            GridTile* newTile = new GridTile(rng->GetNext(), this->Engine);

            newTile->MoveTo(j * BlockSize + (j * SpaceSize) + GridOffsetPosX, i * BlockSize + (i * SpaceSize) + GridOffsetPosY);

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

        info->MoveTo(posOffset.X, posOffset.Y);
    }

    gameTitleText = Engine->CreateText("Down & Across");
    gameTitleText->SetCharacterSize(32);
    gameTitleText->SetPos(10, 0);
    gameTitleText->SetColor(0xFFFFFFFF);

    currentLevelLabel = Engine->CreateText("Level 1");
    currentLevelLabel->SetCharacterSize(32);
    currentLevelLabel->SetPos(300, 0);
    currentLevelLabel->SetColor(0xFFFFFFFF);

    currentLevelScore = Engine->CreateText("0");
    currentLevelScore->SetCharacterSize(72);
    currentLevelScore->SetPos(0, 520);
    currentLevelScore->SetColor(0xFFFFFFFF);

    currentLevelScoreExplain = Engine->CreateText("Current Level Score");
    currentLevelScoreExplain->SetCharacterSize(12);
    currentLevelScoreExplain->SetPos(5, 525);
    currentLevelScoreExplain->SetColor(0xFFFFFFFF);

    totalScoreText = Engine->CreateText("0");
    totalScoreText->SetCharacterSize(72);
    totalScoreText->SetPos(300, 520);
    totalScoreText->SetColor(0xFFFFFFFF);

    totalScoreExplain = Engine->CreateText("Total Score");
    totalScoreExplain->SetCharacterSize(12);
    totalScoreExplain->SetPos(305, 525);
    totalScoreExplain->SetColor(0xFFFFFFFF);


    btnNextLevel = Engine->CreateSprite("btnNextLevel", "assets\\Button_NextLevel.png");
    btnNextLevel->SetScale(0.5);

    FPosition targetPos = InfoTiles->Get(InfoTiles->Count() - 1)->BackgroundSprite->GetOffsetPos();
    targetPos.X += 64 + 10;
    btnNextLevel->SetPos(targetPos);

    // Message setup
    LevelCompleteMessage = new GameMessageWindow();
    LevelCompleteMessage->WindowSprite = Engine->CreateSprite("LevelCompleteMsg", "assets\\DefaultDialogBackground.png");
    LevelCompleteMessage->WindowSprite->SetScale(2.0);
    LevelCompleteMessage->WindowText = Engine->CreateText("Level Complete !");
    LevelCompleteMessage->SetDialogPosition(FPosition(200, 200));
    LevelCompleteMessage->Close();
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

    if (this->CurrentState == GameGridState::PLAYING)
    {
        if (this->Engine->Keyboard->IsKeyClicked(Space))
        {
            this->RandomizeBoardNumbers(4);

            this->RefreshGridTileInformations();
        }

        if (this->Engine->Keyboard->IsKeyClicked(R))
        {
            if (cheatAppliedState == Covered)
            {
                auto it = this->Tiles->GetContainer()->begin();
                while (it != this->Tiles->GetContainer()->end())
                {
                    GridTile* tile = (*it);

                    tile->tileState = Revealed;

                    it++;
                }

                cheatAppliedState = Revealed;
            }
            else
            {
                auto it = this->Tiles->GetContainer()->begin();
                while (it != this->Tiles->GetContainer()->end())
                {
                    GridTile* tile = (*it);

                    tile->tileState = Covered;

                    it++;
                }

                cheatAppliedState = Covered;
            }
        }

        this->UpdateGameScore();

        if (this->btnNextLevel->Clicked())
        {
            this->SkipBoard();
        }

        if (this->BoardIsCleared())
        {
            this->CurrentState = GameGridState::BOARD_FINISHED;

        }
    }
    else if (this->CurrentState == GameGridState::BOARD_FINISHED)
    {
        if (LevelCompleteMessage->IsOpen == false)
        {
            LevelCompleteMessage->Show();
        }
        else
        {
            if (LevelCompleteMessage->WindowSprite->Clicked())
            {
                LevelCompleteMessage->Close();

                this->FinishBoard();

                this->CurrentState = GameGridState::PLAYING;
            }
        }
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

void GameGrid::RandomizeBoardNumbers(int maxPossibleNumber)
{
    auto it = this->Tiles->GetContainer()->begin();
    while (it != this->Tiles->GetContainer()->end())
    {
        GridTile* tile = (*it);

        int newNumber = rng->GetNext();

        tile->SetNewNumber(newNumber);

        it++;
    }

}

void GameGrid::UpdateGameScore()
{
    int boardScore = 1;

    auto it = this->Tiles->GetContainer()->begin();
    while (it != this->Tiles->GetContainer()->end())
    {
        GridTile* tile = (*it);

        if (tile->tileState == Revealed)
        {
            boardScore *= tile->tileNumber;
        }

        it++;
    }

    CurrentLevelScore = boardScore;

    currentLevelScore->SetText(std::to_string(CurrentLevelScore));

    totalScoreText->SetText(std::to_string(TotalScore));
}

void GameGrid::FinishBoard()
{
    CurrentLevelNumber++;

    std::string levelString = std::to_string(CurrentLevelNumber);
    std::string levelLabel = "Level " + levelString;
    currentLevelLabel->SetText(levelLabel);

    auto it = this->Tiles->GetContainer()->begin();
    while (it != this->Tiles->GetContainer()->end())
    {
        GridTile* tile = (*it);

        tile->tileState = Covered;

        it++;
    }

    TotalScore += CurrentLevelScore;

    CurrentLevelScore = 1;

    this->RandomizeBoardNumbers(CurrentLevelNumber);

    this->RefreshGridTileInformations();

    cheatAppliedState = Covered;
}

void GameGrid::SkipBoard()
{
    auto it = this->Tiles->GetContainer()->begin();
    while (it != this->Tiles->GetContainer()->end())
    {
        GridTile* tile = (*it);

        tile->tileState = Covered;

        it++;
    }

    TotalScore += CurrentLevelScore;

    CurrentLevelScore = 1;

    this->RandomizeBoardNumbers(CurrentLevelNumber);

    this->RefreshGridTileInformations();

    cheatAppliedState = Covered;
}

bool GameGrid::BoardIsCleared()
{
    bool boardCleared = true;

    auto it = this->Tiles->GetContainer()->begin();
    while (it != this->Tiles->GetContainer()->end())
    {
        GridTile* tile = (*it);

        if ((tile->tileNumber > 0 && tile->tileState == Covered) || (tile->tileNumber == 0 && tile->tileState == Revealed))
        {
            boardCleared = false;
        }

        it++;
    }

    return boardCleared;
}
