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

void GraphicEngine::Run()
{
	isRunning = true;

	while (window->isOpen())
	{
		if (!isRunning)
			break;

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

void GraphicEngine::Stop()
{
	isRunning = false;
}
