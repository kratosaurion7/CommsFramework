#include "BaseDialog.h"

#include "Graphic/Base Classes/BaseText.h"
#include "Graphic/Base Classes/BaseSprite.h"


BaseDialog::BaseDialog()
{
    //BaseActor::BaseActor();
    DialogState = DIALOG_CLOSED;
}


BaseDialog::~BaseDialog()
{
}

void BaseDialog::Open()
{
    auto it = this->Sprites->GetContainer()->begin();
    while (it != this->Sprites->GetContainer()->end())
    {
        DrawObject* obj = (*it);
        
        obj->Show(true);

        it++;
    }

    DialogState = DIALOG_OPEN;
}

void BaseDialog::Close()
{
    auto it = this->Sprites->GetContainer()->begin();
    while (it != this->Sprites->GetContainer()->end())
    {
        DrawObject* obj = (*it);

        obj->Show(false);

        it++;
    }

    if (DialogState == DIALOG_OPEN)
    {
        DialogState = DIALOG_DONE;
    }
    else
    {
        DialogState = DIALOG_CLOSED;
    }
}

bool BaseDialog::IsOpen()
{
    return DialogState == DIALOG_OPEN;
}

void BaseDialog::Reset()
{
    DialogState = DIALOG_CLOSED;
}

void BaseDialog::Update()
{
}
