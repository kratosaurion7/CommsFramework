#include "GraphicEngine.h"

#include <list>
#include <iterator>
#include <algorithm>

#include <SFML\Graphics.hpp>

#include "DSprite.h"
#include "DTexture.h"
#include "SFMLFont.h"
#include "SFMLText.h"
#include "SFMLDrawable.h"
#include "DrawObject.h"
#include "GraphicEngineInitParams.h"
#include "SFMLKeyboard.h"

GraphicEngine::GraphicEngine()
{
    MainWindow = NULL;
    isRunning = false;
    TextureRepo = new TextureRepository(this);
    Sprites = new PointerList<DrawObject*>();
    startParams = NULL;
    backgroundColor = sf::Color();
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
    spr->Engine = this;

    spr->Ident = identifier;

    return spr;
}

BaseTexture * GraphicEngine::CreateTexture()
{
    DTexture* tex = new DTexture();

    return tex;
}

BaseTexture * GraphicEngine::CreateTexture(std::string texturePath)
{
    BaseTexture* tex = this->TextureRepo->LoadTexture(texturePath);

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

void GraphicEngine::SetBackgroundColor(uint32_t color)
{
    backgroundColor = sf::Color(color);
}

void GraphicEngine::SetBackgroundTexture(BaseTexture * texture)
{
}

void GraphicEngine::AddObject(BaseSprite* obj)
{
    DSprite* dspr = dynamic_cast<DSprite*>(obj);

    if (dspr != NULL) 
    {
        this->zIndexNeedsReordering = true;

        Sprites->Add(dspr);
    }
        
}

void GraphicEngine::AddObject(BaseText* obj)
{
    SFMLText* txt = dynamic_cast<SFMLText*>(obj);

    if (txt != NULL)
    {
        this->zIndexNeedsReordering = true;

        Sprites->Add(txt);
    }
        
}

void GraphicEngine::RemoveObject(DrawObject* obj)
{
    DSprite* dspr = dynamic_cast<DSprite*>(obj);

    if (dspr != NULL)
        Sprites->RemoveObject(dspr);
}

PointerList<DrawObject*>* GraphicEngine::GetDrawableList()
{
    return Sprites;
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

void GraphicEngine::ReorderSpritesByZIndex()
{
    auto spritesStart = this->Sprites->GetContainer()->begin();
    auto spritesEnd = this->Sprites->GetContainer()->end();

    Sprites->GetContainer()->sort([](DrawObject* a, DrawObject* b) {
        return b->GetZIndex() > a->GetZIndex();
    });

    this->zIndexNeedsReordering = false;
}

void GraphicEngine::FlagForZIndexSorting()
{
    zIndexNeedsReordering = true;
}

void GraphicEngine::ReorderSprite(DrawObject* first, DrawObject* second)
{
    std::list<DrawObject*>* spriteslist = this->Sprites->GetContainer();
    bool foundFirst = false;
    bool foundSecond = false;
    std::list<DrawObject*>::iterator iterFirst;
    std::list<DrawObject*>::iterator iterSecond;

    int loops = 0;

    auto it = spriteslist->begin();
    while (it != spriteslist->end())
    {
        DrawObject* iter = (*it);

        if (iter == first) 
        {
            iterFirst = it;
            foundFirst = true;
        }
        else if (iter == second)
        {
            iterSecond = it;
            foundSecond = true;
        }

        if (foundFirst && foundSecond) // Early break
            break;

        it++;
        loops++;
    }

    if (foundFirst && foundSecond)
    {
        spriteslist->erase(iterSecond);

        spriteslist->insert(iterFirst, second);
    }
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
    targetWindow->clear(backgroundColor);

    auto iter = Sprites->GetContainer()->begin();
    while (iter != Sprites->GetContainer()->end())
    {
        DrawObject* targetSprite = (*iter);

        if (targetSprite->IsVisible())
        {
            sf::Drawable* targetDrawable = NULL;

            SFMLDrawable* drawbleObject = dynamic_cast<SFMLDrawable*>(targetSprite);

            if (drawbleObject != NULL)
            {
                targetDrawable = drawbleObject->GetDrawableImplementation();

                targetWindow->draw(*targetDrawable);
            }
        }

        iter++;
    }

    targetWindow->display();
}