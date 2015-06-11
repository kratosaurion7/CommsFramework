#pragma once

#include <SFML\Graphics.hpp>

#include "PointerList.h"

#include "DSprite.h"

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
	BaseList<DSprite*>* Sprites;

	bool isRunning;

	void ProcessWindowsEvents(sf::RenderWindow* targetWindow);

	void ProcessDraw(sf::RenderWindow* targetWindow);

	sf::RenderWindow* window;



};

