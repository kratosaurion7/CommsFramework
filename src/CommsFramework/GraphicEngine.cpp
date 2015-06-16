#include "GraphicEngine.h"

#include "DSprite.h"

#include <list>
#include <iterator>

#include <SFML\Graphics.hpp>

#include "SFMLKeyboard.h"

GraphicEngine::GraphicEngine()
{
	MainWindow = NULL;
	isRunning = false;
	Sprites = new PointerList<DSprite*>();
	Keyboard = new SFMLKeyboard();
}

GraphicEngine::~GraphicEngine()
{
	if (MainWindow == NULL)
		delete MainWindow;

	if (Sprites != NULL)
		Sprites;
}

void GraphicEngine::Initialize(GraphicEngineInitParams* params)
{
	MainWindow = new sf::RenderWindow(sf::VideoMode(params->WindowSize->Height, params->WindowSize->Width), params->WindowTitle->c_str());

	MainWindow->setVerticalSyncEnabled(params->EnableVerticalSync);
}

BaseSprite* GraphicEngine::CreateSprite()
{
	DSprite* spr = new DSprite();
	
	return spr;
}

BaseTexture * GraphicEngine::CreateTexture()
{
	DTexture* tex = new DTexture();

	return tex;
}

void GraphicEngine::AddObject(DrawObject* obj)
{
	DSprite* dspr = dynamic_cast<DSprite*>(obj);

	if(dspr != NULL)
		Sprites->Add(dspr);
}

void GraphicEngine::RemoveObject(DrawObject * obj)
{
	DSprite* dspr = dynamic_cast<DSprite*>(obj);

	if (dspr != NULL)
		Sprites->RemoveObject(dspr);
}

DrawObject * GraphicEngine::GetObject(std::string* identifier)
{
	std::list<DSprite*>::iterator iter = Sprites->GetContainer()->begin();

	while (iter != Sprites->GetContainer()->end())
	{
		// Problem here is that I must present innerImpl as a public member of DSprite. Not very library agnostic.
		// TODO : CHECK FOR LEAKS

		DSprite* targetSprite = (*iter);

		if (targetSprite->Ident == identifier)
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
	
	std::list<DSprite*>::iterator iter = Sprites->GetContainer()->begin();

	while (iter != Sprites->GetContainer()->end())
	{
		// Problem here is that I must present innerImpl as a public member of DSprite. Not very library agnostic.
		// TODO : CHECK FOR LEAKS

		DSprite* targetSprite = (*iter);

		if (targetSprite->IsVisible())
		{
			sf::Sprite innerSprite = (*targetSprite->innerImpl);

			targetWindow->draw(innerSprite);
		}

		iter++;
	}

	targetWindow->display();
}
