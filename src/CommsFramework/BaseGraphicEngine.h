#pragma once

#include "BaseSprite.h"
#include "DrawObject.h"
#include "BaseTexture.h"

class BaseGraphicEngine
{
public:
	virtual void Initialize(GraphicEngineInitParams* params) = 0;

	virtual void AddObject(DrawObject* obj) = 0;

	virtual void RemoveObject(DrawObject* obj) = 0;

	virtual DrawObject* GetObject(std::string* identifier) = 0;

	virtual BaseSprite* CreateSprite() = 0;

	virtual BaseTexture* CreateTexture() = 0;

	virtual void Process() = 0;

	virtual void StartLooping() = 0;

	virtual void Stop() = 0;

};

