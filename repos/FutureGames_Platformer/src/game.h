#pragma once
#include "player.h"
#include "block.h"
#include "camera.h"

#define MAP_COLS 16
#define MAP_ROWS 16
#define NUMBLOCKS (MAP_COLS * MAP_ROWS)


extern Player player;//Stack the plaeyr, put him in stack
extern Block* blocks[MAP_COLS*MAP_ROWS];
extern Camera camera;

void loadMap();






