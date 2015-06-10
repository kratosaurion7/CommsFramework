#pragma once

#include <SFML\Graphics.hpp>

class GraphicEngine
{
public:
	GraphicEngine();
	~GraphicEngine();

	void Initialize();

	void Run();

	void Stop();

private:
	bool isRunning;

	sf::RenderWindow* window;


};

