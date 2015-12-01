#pragma once

#include <string>

#include "IDialog.h"
#include "BaseSprite.h"
#include "BaseActor.h"
#include "BaseText.h"

class YesNoDialog : public BaseActor, public IDialog
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

protected:
    bool _IsOpen;
};