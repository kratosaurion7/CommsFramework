#pragma once

class BaseTexture
{
public:
	virtual void Load(std::string path) = 0;

	virtual FSize* GetSize() = 0;

};