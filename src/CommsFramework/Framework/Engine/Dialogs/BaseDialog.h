#pragma once

#include <string>

#include "Engine/Dialogs/IDialog.h"
#include "Game/Actors/BaseActor.h"


class BaseDialog : public BaseActor, public IDialog
{
public:
    enum DIALOG_STATE
    {
        DIALOG_CLOSED,
        DIALOG_OPEN,
        DIALOG_DONE
    } DialogState;

    BaseDialog();
    ~BaseDialog();

    virtual void Open();
    virtual void Close();
    virtual bool IsOpen();

    virtual void Reset();
protected:
    virtual void Update();
};