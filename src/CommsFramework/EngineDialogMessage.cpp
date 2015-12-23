#include "EngineDialogMessage.h"

#include "BaseSprite.h"
#include "GameEngine.h"
#include "BaseText.h"
#include "BaseTexture.h"
#include "BaseGraphicEngine.h"


EngineDialogMessage::EngineDialogMessage(GameEngine* engine)
{
    this->Engine = engine;

    DialogSprite = this->Engine->CreateSprite("EngineDialogSprite");
    
    BaseTexture* dialogBackgroundTexture = this->Engine->Graphics->CreateTexture("Assets\\DefaultDialogBackground.png");
    DialogSprite->SetTexture(dialogBackgroundTexture);

    DialogSprite->Show(false);
    
    DialogText = this->Engine->CreateText("");
}


EngineDialogMessage::~EngineDialogMessage()
{
}

void EngineDialogMessage::Show(std::string message)
{
    FPosition gameCenterPosition = FPosition();
    gameCenterPosition.X = (this->Engine->GameAreaSize->Width / 2) - (DialogSprite->GetWidth() / 2);
    gameCenterPosition.Y = (this->Engine->GameAreaSize->Height / 2) - (DialogSprite->GetHeight() / 2);

    DialogSprite->SetPos(gameCenterPosition);
    DialogSprite->Show(true);

    DialogText->SetPos(gameCenterPosition.X + 5, gameCenterPosition.Y + 20);
    DialogText->Show(true);
}

void EngineDialogMessage::Show(std::string message, FPosition pos)
{
    isOpen = true;

    DialogText->Show(true);

    DialogSprite->SetPos(pos);
    DialogSprite->Show(true);
}

void EngineDialogMessage::Close()
{
    isOpen = false;

    DialogText->Show(false);
    DialogText->Show(false);

}

bool EngineDialogMessage::IsOpen()
{
    return isOpen;
}
