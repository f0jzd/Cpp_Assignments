#include "player.h"
#include "engine.h"
#include "game.h"
#include "collision.h"

bool space_previous = false;

bool Player::step(float dx, float dy)
{
	if (sweep(dx,dy))
	{
		return false;
	}

	x += dx;
	y += dy;
	return true;
}

bool Player::sweep(float dx, float dy)
{
	if (x + dx < 16.f || x + dx > 1600.f - 16 ||
		y + dy < 16.f || y + dy > 900.f - 16)
	{
		return true;
	}

	AABB player_box = AABB::make_from_position_size(x + dx, y + dy, 32, 32);

	for (int i = 0; i < NUMBLOCKS; i++)
	{

		Block* block = blocks[i];
		if (block == nullptr)
		{
			continue;
		}

		if (aabb_intersect(player_box, block->getCollision()))
		{
			return true;
		}
	}

	

	return false;
}





void Player::update()
{

	if (keys[SDL_SCANCODE_D])
		velocityX += 1500.f * delta_time;

	if (keys[SDL_SCANCODE_A])
		velocityX -= 1500.f * delta_time;

	bool isGrounded = sweep(0.f, 1.5f);


	if (keys[SDL_SCANCODE_SPACE] && !space_previous && isGrounded)
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
	SDL_Rect rect = { (int)x - 16 - camera.x,(int)y - 16 - camera.y,32,32 };
	SDL_RenderFillRect( render, &rect);
}


