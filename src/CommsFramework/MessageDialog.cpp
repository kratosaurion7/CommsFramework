#include "MessageDialog.h"



MessageDialog::MessageDialog()
{
    BaseDialog::BaseDialog();

}

MessageDialog::MessageDialog(std::string message)
{
    BaseDialog::BaseDialog();

    this->dialogMessage = message;

    ClosingMethod = CLICK;

    DialogOpenedMilisecondAmount = 0;

    PreviousMsCount = GetTicks();

    this->SetupSprites();

    this->ClosingMethod = CLICK;
}

MessageDialog::MessageDialog(std::string message, int windowTimeoutMiliseconds)
{
    BaseDialog::BaseDialog();

    this->dialogMessage = message;

    this->MaxOpenTime = windowTimeoutMiliseconds;

    ClosingMethod = CLICK;

    DialogOpenedMilisecondAmount = 0;

    PreviousMsCount = GetTicks();

    this->SetupSprites();

    this->ClosingMethod = CLICK | TIME;
}


MessageDialog::~MessageDialog()
{
    
}

void MessageDialog::Open()
{
    BaseDialog::Open();

    int ticks = GetTicks();
    this->CurrentMsCount = ticks;
    this->PreviousMsCount = ticks;

    DialogOpenedMilisecondAmount = 0;
}

void MessageDialog::Close()
{
    BaseDialog::Close();

    this->DialogSprite->Show(false);
    this->DialogText->Show(false);

    DialogOpenedMilisecondAmount = 0;
}

void MessageDialog::Update()
{
    BaseDialog::Update();

    if (DialogState == BaseDialog::DIALOG_CLOSED)
        return;

    if (this->ClosingMethod | DialogCloseMechanism::TIME)
    {
        CurrentMsCount = GetTicks();

        int delta = CurrentMsCount - PreviousMsCount;

        this->DialogOpenedMilisecondAmount += delta;

        if (this->DialogOpenedMilisecondAmount > this->MaxOpenTime)
        {
            this->Close();
        }

        this->PreviousMsCount = this->CurrentMsCount;
    }

    if (this->ClosingMethod | DialogCloseMechanism::CLICK)
    {
        if (this->DialogSprite->Clicked())
        {
            this->Close();
        }
    }
}

void MessageDialog::SetupSprites()
{
    DialogSprite = Engine->CreateSprite("YesNoDialogMessageFrame");
    DialogSprite->SetTexture("assets\\dialogs\\DialogFrame.png");
    DialogSprite->SetPos(300, 300);

    DialogText = Engine->CreateText(this->dialogMessage);
    DialogText->SetPos(300, 300);

    this->Sprites->Add(DialogSprite);
    this->Sprites->Add(DialogText);
}
