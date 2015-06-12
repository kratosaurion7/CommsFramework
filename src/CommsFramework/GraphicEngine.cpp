#include "GraphicEngine.h"

#include "DSprite.h"

#include <list>
#include <iterator>

#include <SFML\Graphics.hpp>


GraphicEngine::GraphicEngine()
{
	window = NULL;
	isRunning = false;
	Sprites = new PointerList<DSprite*>();
}

GraphicEngine::~GraphicEngine()
{
	if (window == NULL)
		delete window;
}

void GraphicEngine::Initialize(GraphicEngineInitParams* params)
{
	window = new sf::RenderWindow(sf::VideoMode(params->WindowSize->Height, params->WindowSize->Width), params->WindowTitle->c_str());

	window->setVerticalSyncEnabled(params->EnableVerticalSync);
}

void GraphicEngine::Process()
{
	if (window->isOpen())
	{
		ProcessWindowsEvents(window); // Need to process the Windows events no matter what.

		if (isRunning)
		{
			ProcessDraw(window);
		}
	}
}

void GraphicEngine::StartLooping()
{
	isRunning = true;

	while (window->isOpen())
	{
		if (!isRunning)
			break;

		Process();
	}
}

void GraphicEngine::Stop()
{
	isRunning = false;
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
