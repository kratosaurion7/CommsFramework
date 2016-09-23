#pragma once

struct TileDescriptionList;
class Tile;
class BaseTexture;

#include <BaseActor.h>
#include <PointerList.h>

class Map : public BaseActor
{
public:
    Map();
    ~Map();

	static Map* CreateFromXml(std::string xmlPath);

private:

};