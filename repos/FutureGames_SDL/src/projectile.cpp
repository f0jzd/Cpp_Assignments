#include "engine.h"
#include "projectile.h"

void Projectile::update()
{
	if (!alive)
	{
		return;
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
	SDL_Rect rect = { (int)x, (int)y,8,8 };

	SDL_RenderFillRect(render, &rect);

}