#include "player.h"
#include"engine.h"
#include"game.h"

void Player::update()
{
	//möve player

	if (keys[SDL_SCANCODE_D])
		x += 200 * delta_time;

	if (keys[SDL_SCANCODE_A])
		x -= 200 * delta_time;

	if (keys[SDL_SCANCODE_S])
		y += 200 * delta_time;
	
	if (keys[SDL_SCANCODE_W])
		y -= 200 * delta_time;


	shoot_timer -= delta_time;
	if (keys[SDL_SCANCODE_SPACE] && shoot_timer < 0)
	{

		Projectile& proj = projectiles[next_projectile_index];
		proj.alive = true;
		proj.x = x;
		proj.y = y; 

		shoot_timer = 0.2f;//1 second pause we can shoot again.

		next_projectile_index++;
		next_projectile_index = next_projectile_index % PROJECTILE_MAX;
	}
}

void Player::draw()
{
	SDL_Rect rect = { (int)x-16,(int)y-16,32,32 };

	SDL_SetRenderDrawColor(render, 150, 25, 40, 255);

	SDL_RenderFillRect( render, &rect);
}