#include "UIElement.h"

#include "BaseSprite.h"

UIElement::UIElement()
{
    ElementSprites = new PointerList<BaseSprite*>();
}


UIElement::~UIElement()
{
}

void UIElement::Show()
{
    auto it = ITBEGIN(ElementSprites);
    while (it != ITEND(ElementSprites))
    {
        BaseSprite* sprt = *it;

        sprt->Show(true);

        it++;
    }
}

void UIElement::Hide()
{
    auto it = ITBEGIN(ElementSprites);
    while (it != ITEND(ElementSprites))
    {
        BaseSprite* sprt = *it;

        sprt->Show(false);

        it++;
    }
}

void UIElement::Update(MouseClickInfo* mouseInfo)
{
    
}
