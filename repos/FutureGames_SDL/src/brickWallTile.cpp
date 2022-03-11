#include "brickWallTile.h"
#include <SDL/SDL.h>
#include "engine.h"
#include "collision.h"


void Wall::draw()
{

	AABB box = AABB::make_from_position_size(x, y, w, h);
	draw_box(box);
}
