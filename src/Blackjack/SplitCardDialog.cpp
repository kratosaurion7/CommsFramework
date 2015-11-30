#include "SplitCardDialog.h"

SplitCardDialog::SplitCardDialog()
{
    BaseActor::BaseActor();

    DialogSprite = Engine->CreateSprite("SplitSpriteMessageFrame");
    DialogSprite->SetPos(300, 300);

    ButtonYes = Engine->CreateSprite("SplitCardsYesButton");
    ButtonYes->SetPos(300, 300);

    ButtonNo = Engine->CreateSprite("SplitCardsNoButton");
    ButtonNo->SetPos(455, 300);

    DialogText = Engine->CreateText("Split ?");
    DialogText->SetPos(300, 300);

    this->Sprites->Add(DialogSprite);
    this->Sprites->Add(ButtonYes);
    this->Sprites->Add(DialogText);

    _IsOpen = false;
    SplitDecision = DialogResult::CHOOSING;
}


SplitCardDialog::~SplitCardDialog()
{
    
}

void SplitCardDialog::Open()
{
    DialogSprite->Show(true);
    ButtonYes->Show(true);
    ButtonNo->Show(true);
    DialogText->Show(true);

    _IsOpen = true;
}

void SplitCardDialog::Close()
{
    DialogSprite->Show(false);
    ButtonYes->Show(false);
    ButtonNo->Show(false);
    DialogText->Show(false);

    _IsOpen = false;
}

bool SplitCardDialog::IsOpen()
{
    return _IsOpen;
}

void SplitCardDialog::Update()
{
    if (_IsOpen)
    {
        switch (SplitDecision)
        {
            case SplitCardDialog::CHOOSING:
                if (ButtonYes->Clicked())
                {
                    this->SplitDecision = DialogResult::YES;
                }
                else if (ButtonNo->Clicked())
                {
                    this->SplitDecision = DialogResult::NO;
                }

                break;
            case SplitCardDialog::YES:
                break;
            case SplitCardDialog::NO:
                break;
            default:
                break;
        }
    }
}
