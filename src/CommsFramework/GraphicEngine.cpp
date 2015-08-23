#include "GraphicEngine.h"

#include "DSprite.h"
#include "DTexture.h"
#include "SFMLFont.h"
#include "SFMLText.h"

#include <list>
#include <iterator>

#include <SFML\Graphics.hpp>

#include "SFMLKeyboard.h"

GraphicEngine::GraphicEngine()
{
    MainWindow = NULL;
    isRunning = false;
    Sprites = new PointerList<DrawObject*>();
    startParams = NULL;
}

GraphicEngine::~GraphicEngine()
{
    if (MainWindow != NULL)
    {
        MainWindow->close();
        delete(MainWindow);
    }


    if (Sprites != NULL)
    {
        Sprites->Release();
        delete(Sprites);
    }

    delete(startParams);

}

void GraphicEngine::Initialize(GraphicEngineInitParams* params)
{
    startParams = params;

    sf::VideoMode vid = sf::VideoMode(params->WindowSize->Height, params->WindowSize->Width);

    const char* title = params->WindowTitle.c_str();
    MainWindow = new sf::RenderWindow(vid, title);

    MainWindow->setVerticalSyncEnabled(params->EnableVerticalSync);
}

BaseSprite* GraphicEngine::CreateSprite(std::string identifier)
{
    DSprite* spr = new DSprite();

    spr->Ident = identifier;

    return spr;
}

BaseTexture * GraphicEngine::CreateTexture()
{
    DTexture* tex = new DTexture();

    return tex;
}

BaseFont * GraphicEngine::CreateFont()
{
    SFMLFont* font = new SFMLFont();

    return font;
}

BaseText * GraphicEngine::CreateText()
{
    SFMLText* text = new SFMLText();

    return text;
}

int GraphicEngine::GetFramerate()
{
    return _sfmlFramerate;
}

void GraphicEngine::SetFramerate(int framerate)
{
    _sfmlFramerate = framerate;

    MainWindow->setVerticalSyncEnabled(false);
    MainWindow->setFramerateLimit(_sfmlFramerate);
}

void GraphicEngine::SetAutoManagedFramerate(bool isSet)
{
    if(isSet)
        MainWindow->setFramerateLimit(0);

    MainWindow->setVerticalSyncEnabled(isSet);
}

void GraphicEngine::AddObject(BaseSprite* obj)
{
    DSprite* dspr = dynamic_cast<DSprite*>(obj);

    if (dspr != NULL)
        Sprites->Add(dspr);
}

void GraphicEngine::AddObject(BaseText* obj)
{
    SFMLText* txt = dynamic_cast<SFMLText*>(obj);

    if (txt != NULL)
        Sprites->Add(txt);
}

void GraphicEngine::RemoveObject(DrawObject* obj)
{
    DSprite* dspr = dynamic_cast<DSprite*>(obj);

    if (dspr != NULL)
        Sprites->RemoveObject(dspr);
}

DrawObject * GraphicEngine::GetObject(std::string identifier)
{
    std::list<DrawObject*>::iterator iter = Sprites->GetContainer()->begin();

    while (iter != Sprites->GetContainer()->end())
    {
        DrawObject* targetSprite = (*iter);

        if (strcmp(targetSprite->Ident.c_str(), identifier.c_str()) == 0)
        {
            return targetSprite;
        }

        iter++;
    }

    return NULL;
}

void GraphicEngine::Start()
{
    isRunning = true;
}

void GraphicEngine::Draw()
{
    ProcessDraw(MainWindow);
}

void GraphicEngine::ProcessEvents()
{
    ProcessWindowsEvents(MainWindow);
}

void GraphicEngine::Stop()
{
    isRunning = false;
}

bool GraphicEngine::IsRunning()
{
    return isRunning;
}

void GraphicEngine::ProcessWindowsEvents(sf::RenderWindow* targetWindow)
{
    sf::Event event;
    while (targetWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            targetWindow->close();
    }
}

void GraphicEngine::ProcessDraw(sf::RenderWindow* targetWindow)
{
    targetWindow->clear();

    auto iter = Sprites->GetContainer()->begin();
    while (iter != Sprites->GetContainer()->end())
    {
        DrawObject* targetSprite = (*iter);

        if (targetSprite->IsVisible())
        {
            sf::Drawable* targetDrawable;

            SFMLDrawable* drawbleObject = dynamic_cast<SFMLDrawable*>(targetSprite);

            if (drawbleObject != NULL)
            {
                targetDrawable = drawbleObject->GetDrawableImplementation();
            }

            targetWindow->draw(*targetDrawable);
        }

        iter++;
    }

    targetWindow->display();
}
