#include "SFMLGraphicEngine.h"

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

SFMLGraphicEngine::SFMLGraphicEngine()
{
    MainWindow = NULL;
    isRunning = false;
    TextureRepo = new TextureRepository(this);
    Sprites = new PointerList<DrawObject*>();
    startParams = NULL;
    backgroundColor = sf::Color();
}

SFMLGraphicEngine::~SFMLGraphicEngine()
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

void SFMLGraphicEngine::Initialize(GraphicEngineInitParams* params)
{
    startParams = params;

    sf::VideoMode vid = sf::VideoMode(params->WindowSize->Height, params->WindowSize->Width);

    const char* title = params->WindowTitle.c_str();
    MainWindow = new sf::RenderWindow(vid, title);

    MainWindow->setVerticalSyncEnabled(params->EnableVerticalSync);
}

BaseSprite* SFMLGraphicEngine::CreateSprite(std::string identifier)
{
    DSprite* spr = new DSprite();
    spr->Engine = this;

    spr->Ident = identifier;

    return spr;
}

BaseTexture * SFMLGraphicEngine::CreateTexture()
{
    DTexture* tex = new DTexture();

    return tex;
}

BaseTexture * SFMLGraphicEngine::CreateTexture(std::string texturePath)
{
    BaseTexture* tex = this->TextureRepo->LoadTexture(texturePath);

    return tex;
}

BaseFont * SFMLGraphicEngine::CreateFont()
{
    SFMLFont* font = new SFMLFont();

    return font;
}

BaseText * SFMLGraphicEngine::CreateText()
{
    SFMLText* text = new SFMLText();

    return text;
}

int SFMLGraphicEngine::GetFramerate()
{
    return _sfmlFramerate;
}

void SFMLGraphicEngine::SetFramerate(int framerate)
{
    _sfmlFramerate = framerate;

    MainWindow->setVerticalSyncEnabled(false);
    MainWindow->setFramerateLimit(_sfmlFramerate);
}

void SFMLGraphicEngine::SetAutoManagedFramerate(bool isSet)
{
    if(isSet)
        MainWindow->setFramerateLimit(0);

    MainWindow->setVerticalSyncEnabled(isSet);
}

void SFMLGraphicEngine::SetBackgroundColor(uint32_t color)
{
    backgroundColor = sf::Color(color);
}

void SFMLGraphicEngine::SetBackgroundTexture(BaseTexture * texture)
{
}

void SFMLGraphicEngine::AddObject(BaseSprite* obj)
{
    DSprite* dspr = dynamic_cast<DSprite*>(obj);

    if (dspr != NULL) 
    {
        this->zIndexNeedsReordering = true;

        Sprites->Add(dspr);
    }
        
}

void SFMLGraphicEngine::AddObject(BaseText* obj)
{
    SFMLText* txt = dynamic_cast<SFMLText*>(obj);

    if (txt != NULL)
    {
        this->zIndexNeedsReordering = true;

        Sprites->Add(txt);
    }
        
}

void SFMLGraphicEngine::RemoveObject(DrawObject* obj)
{
    DSprite* dspr = dynamic_cast<DSprite*>(obj);

    if (dspr != NULL)
        Sprites->RemoveObject(dspr);
}

PointerList<DrawObject*>* SFMLGraphicEngine::GetDrawableList()
{
    return Sprites;
}

DrawObject * SFMLGraphicEngine::GetObject(std::string identifier)
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

void SFMLGraphicEngine::Start()
{
    isRunning = true;
}

void SFMLGraphicEngine::Draw()
{
    ProcessDraw(MainWindow);
}

void SFMLGraphicEngine::ProcessEvents()
{
    ProcessWindowsEvents(MainWindow);
}

void SFMLGraphicEngine::Stop()
{
    isRunning = false;
}

bool SFMLGraphicEngine::IsRunning()
{
    return isRunning;
}

void SFMLGraphicEngine::ReorderSpritesByZIndex()
{
    auto spritesStart = this->Sprites->GetContainer()->begin();
    auto spritesEnd = this->Sprites->GetContainer()->end();

    Sprites->GetContainer()->sort([](DrawObject* a, DrawObject* b) {
        return b->GetZIndex() > a->GetZIndex();
    });

    this->zIndexNeedsReordering = false;
}

void SFMLGraphicEngine::FlagForZIndexSorting()
{
    zIndexNeedsReordering = true;
}

void SFMLGraphicEngine::ReorderSprite(DrawObject* first, DrawObject* second)
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

void SFMLGraphicEngine::ProcessWindowsEvents(sf::RenderWindow* targetWindow)
{
    sf::Event event;
    while (targetWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            targetWindow->close();
    }
}

void SFMLGraphicEngine::ProcessDraw(sf::RenderWindow* targetWindow)
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