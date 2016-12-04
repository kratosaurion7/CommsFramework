#include "UIMenu.h"

#include "UIElement.h"
#include "FPosition.h"
#include "BaseSprite.h"


UIMenu::UIMenu(GameEngine* engine)
{
    this->Engine = engine;

    Elements = new PointerList<UIElement*>();

    this->MenuArea.Set(0, 0, 0, 0);
}


UIMenu::~UIMenu()
{
    Elements->Release();
    delete(Elements);
}

void UIMenu::Show()
{
    this->BackgroundImage->Show(true);

    auto it = ITBEGIN(Elements);
    while (it != ITEND(Elements))
    {
        UIElement* element = *it;

        element->Show();

        it++;
    }

}

void UIMenu::Hide()
{
    this->BackgroundImage->Show(false);

    auto it = ITBEGIN(Elements);
    while (it != ITEND(Elements))
    {
        UIElement* element = *it;

        element->Hide();

        it++;
    }

}

void UIMenu::Update(MouseClickInfo* clickInfo)
{
    auto it = ITBEGIN(Elements);
    while(it != ITEND(Elements))
    {
        UIElement* element = *it;

        element->Update(clickInfo);

        it++;
    }
}

void UIMenu::AddElement(UIElement* newElement)
{
    Elements->Add(newElement);
}

void UIMenu::RemoveElement(UIElement* element)
{
    Elements->RemoveObject(element);
}

void UIMenu::RegisterBackgroundImageAndSetSize(BaseSprite* sprite)
{
    if (sprite != NULL)
    {
        this->BackgroundImage = sprite;

        this->MenuArea.Set(0, 0, sprite->GetWidth(), sprite->GetHeight());
    }
}
