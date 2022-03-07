#include "player.h"
#include"engine.h"
#include"game.h"
#include "collision.h"

void Player::update()
{

	if (!ballFired)
	{
		Projectile& proj = projectiles[0];
		proj.alive = true;

		proj.x = player.x;
		proj.y = player.y - 16;
	}

	//möve player

	if (keys[SDL_SCANCODE_D])
		x += playerMovementspeed * delta_time;

	if (keys[SDL_SCANCODE_A])
		x -= playerMovementspeed * delta_time;

	if (keys[SDL_SCANCODE_S])
		y += playerMovementspeed * delta_time;
	
	if (keys[SDL_SCANCODE_W])
		y -= playerMovementspeed * delta_time;


	shoot_timer -= delta_time;
	if (keys[SDL_SCANCODE_SPACE] && !player.ballFired)//HERE WE FIRE BULLET; ENEMY GO boom.
	{
		ballFired = true;


		Projectile& proj = projectiles[next_projectile_index];
		//proj.alive = true;


		proj.velocity_y = -500.f;
		
		/*
		proj.x = x;
		proj.y = y-32; 

		
		shoot_timer = 0.2f;//1 second pause we can shoot again.

		next_projectile_index++;
		next_projectile_index = next_projectile_index % PROJECTILE_MAX;*/
	}
}

void Player::draw()
{

	
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect = { x,y,player.playerWidth, player.playerHeight };
	SDL_Rect rect2 = { x-player.playerWidth,y,player.playerWidth, player.playerHeight };

	/*SDL_RenderDrawLine(render, player.x, player.y, player.x + 32, player.y);
	SDL_SetRenderDrawColor(render, 0, 255, 255, 255);
	SDL_RenderDrawLine(render,player.x,player.y,player.x-32,player.y);*/
	

	



	SDL_RenderFillRect( render, &rect);
	SDL_RenderFillRect( render, &rect2);
}

void Player::DrawBall()
{
	Projectile& proj = projectiles[0];
	proj.alive = true;

	proj.x = player.x;
	proj.y = player.y - 16;
}


