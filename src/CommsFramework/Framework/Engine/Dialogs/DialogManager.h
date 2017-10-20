#pragma once

#include "PointerList.h"
#include "GameEngine.h"

#include "EngineDialogMessage.h"

#include <string>

class DialogManager
{
public:
    DialogManager(GameEngine* engine);
    ~DialogManager();

    PointerList<EngineDialogMessage*>* Dialogs;

    void ShowDialog(std::string message);

    bool HasDialogOpen();
private:
    GameEngine* Engine;
};

