#pragma once

#include <PointerList.h>
#include <BaseActor.h>
#include <BaseText.h>
#include <BaseSprite.h>
#include <GameMessageWindow.h>
#include <WeightedNumberGenerator.h>

#include "GridTile.h"
#include "InfoTile.h"

struct GameGridState {
    enum GridState
    {
        PLAYING,
        BOARD_FINISHED
    };
};

class GameGrid : public BaseActor
{
public:
    GameGrid(int squareSize, GameEngine* engine);
    ~GameGrid();

    GameGridState::GridState CurrentState;

    void Setup();

    int SquareSize;

    int BlockSize = 64;

    int SpaceSize = 20;

    int GridOffsetPosX = 50;
    int GridOffsetPosY = 50;

    int CurrentLevelScore = 0;
    int TotalScore = 0;

    int CurrentLevelNumber = 1;

    void RefreshGridTileInformations();

protected:
    virtual void Update();

private:
    // Textures
    BaseTexture* blockTexture;
    BaseTexture* btnNextLevelTexture;

    // Game Texts
    BaseText* gameTitleText;
    BaseText* currentLevelLabel;

    BaseText* currentLevelScoreExplain;
    BaseText* currentLevelScore;

    BaseText* totalScoreExplain;
    BaseText* totalScoreText;

    // Button Sprite
    BaseSprite* btnNextLevel;

    // Messages
    GameMessageWindow* LevelCompleteMessage;

    WeightedNumberGenerator* rng;

    PointerList<GridTile*>* Tiles;

    PointerList<InfoTile*>* InfoTiles;

    int GetZeroesOfRow(int rowNb);
    int GetSumOfRow(int rowNb);

    int GetZeroesOfColumn(int colNb);
    int GetSumOfColumn(int colNb);

    void RandomizeBoardNumbers(int maxPossibleNumber);

    void UpdateGameScore();

    void FinishBoard();

    void SkipBoard();

    bool BoardIsCleared();

    GridTileState cheatAppliedState = Covered;
};

