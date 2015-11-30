#pragma once

#include <BaseActor.h>
#include <IDialog.h>

class AskNewCardDialog : public BaseActor, public IDialog
{
public:
    enum DialogResult
    {
        CHOOSING,
        YES,
        NO
    } NewCardDecision;

    BaseSprite* DialogSprite;
    BaseSprite* ButtonYes;
    BaseSprite* ButtonNo;
    BaseText* DialogText;

    AskNewCardDialog();
    ~AskNewCardDialog();

    void Open();
    void Close();
    bool IsOpen();

    void Update();

private:
    bool _IsOpen;

};

