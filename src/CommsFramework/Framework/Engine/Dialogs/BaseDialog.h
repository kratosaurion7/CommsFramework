#pragma once

#include <string>

#include "IDialog.h"
#include "BaseSprite.h"
#include "BaseActor.h"
#include "BaseText.h"


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