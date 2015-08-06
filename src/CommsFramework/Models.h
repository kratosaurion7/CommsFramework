#pragma once

#include "FPosition.h"

#include "FSize.h"

class SpriteDescriptor {
public:
	SpriteDescriptor();

	~SpriteDescriptor();

	FPosition* position;
	FSize* size;

};