#pragma once

#include "GameObject.h"

#include "FPosition.h"
#include "FRectangle.h"
#include "FSize.h"

class DrawObject : public GameObject
{
public:
	virtual void Show(bool show) = 0;
	virtual bool IsVisible() = 0;

	virtual float GetX() = 0;
	virtual float GetY() = 0;

	virtual void SetX(float value) = 0;
	virtual void SetY(float value) = 0;

	virtual void IncrementX(float value) = 0;
	virtual void IncrementY(float value) = 0;

	virtual FPosition* GetPos() = 0;
	virtual void SetPos(float x, float y) = 0;
	virtual void SetPos(FPosition* value) = 0;
	virtual void SetCenterPos(FPosition* value) = 0;

	virtual FRectangle* GetRectangle() = 0;

	virtual float GetHeight() = 0;
	virtual float GetWidth() = 0;

	virtual void SetHeight(float height) = 0;
	virtual void SetWidth(float width) = 0;

	virtual FSize* GetSize() = 0;
	virtual void SetSize(float height, float width) = 0;
	virtual void SetSize(FSize* value) = 0;

};