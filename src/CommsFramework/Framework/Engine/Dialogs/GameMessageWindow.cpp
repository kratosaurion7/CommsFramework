#include "GameMessageWindow.h"

GameMessageWindow::GameMessageWindow()
{
    IsOpen = false;
}

GameMessageWindow::~GameMessageWindow()
{
}

void GameMessageWindow::SetDialogPosition(FPosition pos)
{
    WindowSprite->SetPos(pos);

    FPosition textOffsetPos = FPosition(pos);
    textOffsetPos.X += 5;
    textOffsetPos.Y += 5;

    WindowText->SetPos(textOffsetPos);
}

void GameMessageWindow::Show()
{
    IsOpen = true;

    WindowSprite->Show(true);
    WindowText->Show(true);
}

void GameMessageWindow::Close()
{
    IsOpen = false;

    WindowSprite->Show(false);
    WindowText->Show(false);
}
