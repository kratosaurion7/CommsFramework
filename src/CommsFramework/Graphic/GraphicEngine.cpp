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

void GraphicEngine::Initialize()
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "SFML works!");

	window->setVerticalSyncEnabled(true);

}

void GraphicEngine::Process()
{
	if (window->isOpen() && isRunning)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		//window.draw(shape);
		//window->draw(spr);
		window->display();
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
