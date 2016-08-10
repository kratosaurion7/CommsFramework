#pragma once

#define NB_TILES_W 5
#define NB_TILES_H 5

#define TILE_W 65
#define TILE_H 65

#define TILE_SCALE 1.2


#define TILE_TOTAL_W TILE_W * TILE_SCALE
#define TILE_TOTAL_H TILE_H * TILE_SCALE


class GameButton;

extern GameButton*** Board;