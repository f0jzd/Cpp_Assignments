#include "engine.h"
#include "projectile.h"
#include "collision.h"
#include "game.h"

void Projectile::update()
{
	if (!alive)
	{
		return;
	}

	Circle circle = { x, y, 4 };
	draw_circle(circle);


	for (int i = 0; i < BRICK_MAX; i++)
	{
		Brick& brick = bricks[i];
		
		if (!brick.alive)
				continue;
		

		AABB box = AABB::make_from_position_size(brick.x, brick.y, brick.w, brick.h);


		if (aabb_circle_intersect(box, circle))
		{
			alive = false;
			brick.alive = false;
			return;
		}
	}
	

	x += 400 * delta_time;

}
void Projectile::draw()
{

	if (!alive)
	{
		return;
	}

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect = { (int)x-4, (int)y-4,8,8 };

	SDL_RenderFillRect(render, &rect);

}