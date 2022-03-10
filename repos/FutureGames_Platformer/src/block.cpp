#include "block.h"
#include <SDL/SDL.h>
#include "engine.h"
#include "game.h"
void Block::draw()
{
	SDL_Rect rect = { (int)x-camera.x,(int)y-camera.y,32,32 };
	SDL_SetRenderDrawColor(render, 209,131,79,255);
	SDL_RenderFillRect(render, &rect);

}