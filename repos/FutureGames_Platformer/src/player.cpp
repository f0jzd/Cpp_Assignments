#include "player.h"
#include"engine.h"
#include"game.h"
#include "collision.h"

bool space_previous = false;

bool Player::step(float dx, float dy)
{
	if (x+dx < 16.f ||  x + dx > 1600.f- 16 || 
		y+dy < 16.f ||  y + dy > 900.f - 16)
	{
		return false;
	}

	x += dx;
	y += dy;
	return true;
}





void Player::update()
{

	if (keys[SDL_SCANCODE_D])
		velocityX += 500.f * delta_time;

	if (keys[SDL_SCANCODE_A])
		velocityX -= 500.f * delta_time;

	if (keys[SDL_SCANCODE_SPACE] && !space_previous)
	{
		velocityY -= 2000.f;
	}
	space_previous = keys[SDL_SCANCODE_SPACE];

	//Apply gravity

	velocityY += 1200.f * delta_time;

	//Apply friction

	velocityX -= velocityX * 2.5f * delta_time;
	velocityY -= velocityY * 2.5f * delta_time;


	//Apply velocity to position.
	
	if (!step(velocityX * delta_time, 0))
	{
		velocityX = -velocityX * 0.5f;
	}


	if (!step(0, velocityY * delta_time))
	{
		velocityY = -velocityY * 0.5f;
	}





}

void Player::CheckMovement()
{
	
}

void Player::draw()
{

	
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect = { x,y,player.playerWidth, player.playerHeight };
	
	

	



	SDL_RenderFillRect( render, &rect);
}


