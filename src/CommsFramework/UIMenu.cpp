#include "UIMenu.h"

#include "UIElement.h"
#include "UIButton.h"
#include "FPosition.h"
#include "BaseSprite.h"

#include "GameEngine.h"

UIMenu::UIMenu(GameEngine* engine)
{
    this->Engine = engine;

    Elements = new PointerList<UIElement*>();

    this->MenuArea.Set(0, 0, 0, 0);

    Visible = false;
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

    Visible = true;
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

    Visible = false;
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

UIImage* UIMenu::CreateImage(std::string imagePath)
{
    return NULL;
}

/**
 * This interface for UI Elements creation, through CreateXX() methods in the UIMenu class is a simplified mean
 * of creating elements and attaching them to the UIMenu instance.
 *
 * It comes with the cost of having to make a new function here every time a new type of UIElement is introduced.
 * It also means that this function will need to have perhaps too many parameters in order to control the 
 * behavior of the new elements.
*/
UIButton* UIMenu::CreateButton(std::string idleImage, std::string disabled, std::string pushed, std::string hovered)
{
    BaseSprite* btnIdle = this->Engine->CreateSprite("", idleImage);
    btnIdle->SetZIndex(PRIO::UI);
    btnIdle->Show(true);

    BaseSprite* btnDisabled = NULL;
    if (disabled != "")
    {
        btnDisabled = this->Engine->CreateSprite("", disabled);
        btnDisabled->SetZIndex(PRIO::UI);
        btnDisabled->Show(false);
    }

    BaseSprite* btnPushed = NULL;
    if (pushed != "")
    {
        btnPushed = this->Engine->CreateSprite("", pushed);
        btnPushed->SetZIndex(PRIO::UI);
        btnPushed->Show(false);
    }

    BaseSprite* btnHovered = NULL;
    if (hovered != "")
    {
        btnHovered = this->Engine->CreateSprite("", hovered);
        btnHovered->SetZIndex(PRIO::UI);
        btnHovered->Show(false);
    }

    UIButton* createdButton = new UIButton(btnIdle, btnDisabled, btnPushed, btnHovered);

    this->AddElement(createdButton);

    return createdButton;
}