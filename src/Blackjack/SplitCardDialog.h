#pragma once

#include <BaseActor.h>
#include <IDialog.h>

class SplitCardDialog : public BaseActor, public IDialog
{
public:
    enum DialogResult
    {
        CHOOSING,
        YES,
        NO
    } SplitDecision;

    BaseSprite* DialogSprite;
    BaseSprite* ButtonYes;
    BaseSprite* ButtonNo;
    BaseText* DialogText;

    SplitCardDialog();
    ~SplitCardDialog();

    void Open();
    void Close();
    bool IsOpen();

    void Update();

private:
    bool _IsOpen;
};