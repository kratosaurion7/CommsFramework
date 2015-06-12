#pragma once

#include <SFML\Graphics.hpp>

#include "PointerList.h"

#include "DSprite.h"

#include "GraphicEngineInitParams.h"

#include "BaseGraphicEngine.h"

class GraphicEngine : public BaseGraphicEngine
{
public:
	GraphicEngine();
	~GraphicEngine();

	void Initialize(GraphicEngineInitParams* params);

	void AddObject(DrawObject* obj);
	void RemoveObject(DrawObject* obj);
	DrawObject* GetObject(std::string* identifier);
	BaseSprite* CreateSprite();
	BaseTexture* CreateTexture();

	void Process();
    void StartLooping();

	void Stop();

	BaseList<DSprite*>* Sprites;
private:
	

	bool isRunning;

	void ProcessWindowsEvents(sf::RenderWindow* targetWindow);

	void ProcessDraw(sf::RenderWindow* targetWindow);

	sf::RenderWindow* window;



};

