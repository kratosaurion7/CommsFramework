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
	//targetWindow.draw(shape);
	
	std::list<DSprite*>::iterator iter = Sprites->GetContainer()->begin();

	while (iter != Sprites->GetContainer()->end())
	{
		// TODO : CHECK FOR LEAKS
		sf::Sprite innerSprite = (*(*iter)->innerImpl); // Dereference the iterator to get the inner object, then need to dereference the DSPrite's InnerImpl to get the value itself.

		targetWindow->draw(innerSprite);
		//(*iter)->Update(this->CreateGameContext());

		iter++;
	}

	//targetWindow->draw(spr);

	targetWindow->display();

}
