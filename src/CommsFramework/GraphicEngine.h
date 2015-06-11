#pragma once

#include <SFML\Graphics.hpp>



#include "GraphicEngineInitParams.h"


class GraphicEngine
{
public:
	GraphicEngine();
	~GraphicEngine();

	void Initialize(GraphicEngineInitParams* params);

	void Process();
    void StartLooping();

	void Stop();

private:


	bool isRunning;

	void ProcessWindowsEvents(sf::RenderWindow* targetWindow);

	void ProcessDraw(sf::RenderWindow* targetWindow);

	sf::RenderWindow* window;



};

