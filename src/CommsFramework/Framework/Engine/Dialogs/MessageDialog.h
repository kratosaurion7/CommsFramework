#pragma once

class BaseSprite;
class BaseActor;
class BaseText;
class BaseDialog;

#include <string>


#include "BaseDialog.h"

// TODO : Add a BaseDialog class
class MessageDialog : public BaseDialog
{
public:
    enum DialogCloseMechanism
    {
        CLICK = 1,
        TIME = 2
    };
    
    int ClosingMethod;

    BaseSprite* DialogSprite;
    BaseText* DialogText;

    MessageDialog();
    MessageDialog(std::string message);
    MessageDialog(std::string message, int windowTimeoutMiliseconds);
    ~MessageDialog();

    void Open();
    void Close();

protected:
    void Update();

private:
    void SetupSprites();

    int PreviousMsCount;
    int CurrentMsCount;

    int MaxOpenTime;
    int DialogOpenedMilisecondAmount;

    std::string dialogMessage;
};

