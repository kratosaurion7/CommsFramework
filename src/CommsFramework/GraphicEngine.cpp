#include "GraphicEngine.h"

#include <SFML\Graphics.hpp>


GraphicEngine::GraphicEngine()
{
	window = NULL;
	isRunning = false;
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
	//targetWindow->draw(spr);
	targetWindow->display();

}
