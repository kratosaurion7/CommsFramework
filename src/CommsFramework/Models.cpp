#include "Models.h"

SpriteDescriptor::SpriteDescriptor()
{

}

SpriteDescriptor::~SpriteDescriptor()
{
	delete(position);
	delete(size);
}
