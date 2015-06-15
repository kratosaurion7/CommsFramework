#pragma once

#include "BaseSprite.h"
#include "DrawObject.h"
#include "BaseTexture.h"
#include "BaseKeyboard.h"

#include "GraphicEngineInitParams.h"

class BaseGraphicEngine
{
public:
	BaseKeyboard* Keyboard;

	virtual void Initialize(GraphicEngineInitParams* params) = 0;

	virtual void AddObject(DrawObject* obj) = 0;

	virtual void RemoveObject(DrawObject* obj) = 0;

	virtual DrawObject* GetObject(std::string* identifier) = 0;

	virtual BaseSprite* CreateSprite() = 0;

	virtual BaseTexture* CreateTexture() = 0;

	virtual void Start() = 0;

	virtual void Draw() = 0;

	virtual void ProcessEvents() = 0;

	virtual void Stop() = 0;

	virtual bool IsRunning() = 0;
};

