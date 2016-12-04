#include "UIMenu.h"


//class UIElement;
//class BaseGraphicEngine;
//class FPosition;

#include "UIElement.h"
#include "FPosition.h"


UIMenu::UIMenu()
{
    Elements = new PointerList<UIElement*>();
}


UIMenu::~UIMenu()
{
    Elements->Release();
    delete(Elements);
}

void UIMenu::Show()
{
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
