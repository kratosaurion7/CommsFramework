#pragma once

#include <string>

#include "IDialog.h"
#include "BaseSprite.h"
#include "BaseActor.h"
#include "BaseText.h"
#include "BaseDialog.h"

class YesNoDialog : public BaseDialog
{
public:
    enum DialogResult
    {
        CHOOSING,
        YES,
        NO
    } DialogDecision;

    BaseSprite* DialogSprite;
    BaseSprite* ButtonYes;
    BaseSprite* ButtonNo;
    BaseText* DialogText;


    YesNoDialog();
    YesNoDialog(std::string windowText);
    ~YesNoDialog();

    virtual void Open();
    virtual void Close();
    virtual bool IsOpen();

    virtual void Update();
    virtual void ResetDialog();

protected:
    bool _IsOpen;
};