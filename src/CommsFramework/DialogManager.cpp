#include "DialogManager.h"



DialogManager::DialogManager(GameEngine* engine)
{
    this->Engine = engine;
    Dialogs = new PointerList<EngineDialogMessage*>();
}


DialogManager::~DialogManager()
{
    Dialogs->Release();
    delete(Dialogs);
}

void DialogManager::ShowDialog(std::string message)
{
    EngineDialogMessage* newDialog = new EngineDialogMessage(this->Engine);
}

bool DialogManager::HasDialogOpen()
{
    return this->Dialogs->Count() > 0;
}
