#include "brick.h"
#include "collision.h"
#include <SDL/SDL.h>
#include "engine.h"

void Brick::draw()
{
	if (!alive)
	{
		return;
	}

	SDL_SetRenderDrawColor(render, 200, 0, 200, 255);
	AABB box = AABB::make_from_position_size(x, y, w, h);
	draw_box(box);

}