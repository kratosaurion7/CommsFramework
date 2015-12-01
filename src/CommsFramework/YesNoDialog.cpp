#include "YesNoDialog.h"



YesNoDialog::YesNoDialog()
{
    BaseActor::BaseActor();

    DialogSprite = Engine->CreateSprite("SplitSpriteMessageFrame");
    DialogSprite->SetPos(300, 300);

    ButtonYes = Engine->CreateSprite("SplitCardsYesButton");
    ButtonYes->SetPos(300, 300);

    ButtonNo = Engine->CreateSprite("SplitCardsNoButton");
    ButtonNo->SetPos(455, 300);

    DialogText = Engine->CreateText("");
    DialogText->SetPos(300, 300);

    // TODO : Add images to the sprites
    // TODO : Auto arrange the sprite's position

    this->Sprites->Add(DialogSprite);
    this->Sprites->Add(ButtonYes);
    this->Sprites->Add(DialogText);

    _IsOpen = false;
    DialogDecision = DialogResult::CHOOSING;
}

YesNoDialog::YesNoDialog(std::string windowText)
{
    BaseActor::BaseActor();

    DialogSprite = Engine->CreateSprite("SplitSpriteMessageFrame");
    DialogSprite->SetPos(300, 300);

    ButtonYes = Engine->CreateSprite("SplitCardsYesButton");
    ButtonYes->SetPos(300, 300);

    ButtonNo = Engine->CreateSprite("SplitCardsNoButton");
    ButtonNo->SetPos(455, 300);

    DialogText = Engine->CreateText(windowText);
    DialogText->SetPos(300, 300);

    this->Sprites->Add(DialogSprite);
    this->Sprites->Add(ButtonYes);
    this->Sprites->Add(DialogText);

    _IsOpen = false;
    DialogDecision = DialogResult::CHOOSING;
}


YesNoDialog::~YesNoDialog()
{
}

void YesNoDialog::Open()
{
    DialogSprite->Show(true);
    ButtonYes->Show(true);
    ButtonNo->Show(true);
    DialogText->Show(true);

    _IsOpen = true;
}

void YesNoDialog::Close()
{
    DialogSprite->Show(false);
    ButtonYes->Show(false);
    ButtonNo->Show(false);
    DialogText->Show(false);

    _IsOpen = false;
}

bool YesNoDialog::IsOpen()
{
    return _IsOpen;
}

void YesNoDialog::Update()
{
    if (_IsOpen)
    {
        switch (DialogDecision)
        {
            case YesNoDialog::CHOOSING:
                if (ButtonYes->Clicked())
                {
                    this->DialogDecision = DialogResult::YES;
                }
                else if (ButtonNo->Clicked())
                {
                    this->DialogDecision = DialogResult::NO;
                }

                break;
            case YesNoDialog::YES:
                break;
            case YesNoDialog::NO:
                break;
            default:
                break;
        }
    }
}

void YesNoDialog::ResetDialog()
{
    this->Close();

    this->DialogDecision = YesNoDialog::DialogResult::CHOOSING;
}