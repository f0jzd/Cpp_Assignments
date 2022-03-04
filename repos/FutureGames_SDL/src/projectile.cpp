#include "engine.h"
#include "projectile.h"
#include "collision.h"
#include "game.h"

float sign(float a) { return a > 0.f ? 1.f : -1.f; }

void Projectile::update()
{
	if (!alive)
	{
		return;
	}

	if (!step(velocity_x*delta_time,0.f))
	{
		velocity_x = -velocity_x + sign(-velocity_x) *  10.f;
	}
	if (!step(0.f, velocity_y * delta_time))
	{
		velocity_y = -velocity_y + sign(-velocity_y) * 10.f;
	}

	step(velocity_x * delta_time,0.f);
	step(0.f, velocity_y * delta_time);

	//x += velocity_x * delta_time;
	//y += velocity_y * delta_time;

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
 
bool Projectile::step(float dx, float dy)
{
	//Collision check with brick.
	Circle circle = { x+dx, y+dy, 4 };//Next collider of the bullet/ delta is change
	draw_circle(circle);

	AABB box = AABB::make_from_position_size(player.x, player.y, 32, 32);
	draw_box(box);


	for (int i = 0; i < BRICK_COLUMNS; i++)//Here we check collisions with all the bricks
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{


			Brick& brick = bricks[i][j];

			if (!brick.alive)
				continue;


			AABB box = AABB::make_from_position_size(brick.x, brick.y, brick.w, brick.h);


			if (aabb_circle_intersect(box, circle))//If the circle and box intersect a.k.a. the bullet and the brick, then something happens
			{
				//return false;

				alive = false;
				brick.alive = false;
				return false;
			}
		}

	}

	

	if (aabb_circle_intersect(box,circle))
	{
		return false;
	}



	//Check collision with game borders.
	if (x+dx < 0 || x+dx >= 1600 ||
		y+dy < 0 || y+dy >= 900)
	{
	return false;
	}
	

	x += dx;
	y += dy;
	return true;
}
