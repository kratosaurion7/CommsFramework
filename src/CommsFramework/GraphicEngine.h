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

	DrawObject* GetObject(std::string identifier);

	BaseSprite* CreateSprite();
	BaseTexture* CreateTexture();
	BaseFont* CreateFont();
	BaseText* CreateText();

	void Start();

	void Draw();

	void ProcessEvents();

	void Stop();

	BaseList<DSprite*>* Sprites;

	bool IsRunning();

	sf::RenderWindow* MainWindow;

private:
	

	bool isRunning;

	void ProcessWindowsEvents(sf::RenderWindow* targetWindow);

	void ProcessDraw(sf::RenderWindow* targetWindow);

	



};

