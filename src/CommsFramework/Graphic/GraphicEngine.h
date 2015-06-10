#pragma once

#include <SFML\Graphics.hpp>

class GraphicEngine
{
public:
	GraphicEngine();
	~GraphicEngine();

	void Initialize();

	void Process();
    void StartLooping();

	void Stop();

private:
	bool isRunning;

	sf::RenderWindow* window;


};

