#pragma once

#include "Collections/PointerList.h"
#include "Engine/GameEngine.h"
#include "Engine/Dialogs/EngineDialogMessage.h"

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

