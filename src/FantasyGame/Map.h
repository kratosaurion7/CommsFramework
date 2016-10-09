#pragma once

class Tile;

#include <PointerList.h>

class Map
{
public:
	
    Map(int width, int height);
    ~Map();

	static Map* CreateFromXml(std::string xmlPath);

	std::string MapName;

	// Bounds of the map
	int Height;
	int Width;
	
	// 2D array of tile pointers
	Tile*** Tiles;

	// Linked list of Tiles for easier access, albeit slower.
	PointerList<Tile*>* TilesList;

private:
    void InitializeDefaultMap();
};