#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include "engine.h"
#include "player.h"
#include "game.h"
#include "collision.h"

#define WIDTH 1600
#define HEIGHT 900
#define IMG_PATH "image.png"

int main()
{


	SDL_Init(SDL_INIT_EVERYTHING);//Initialize the usage of everything
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0); //A structure to refer to the window we just made
	render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_Texture* img = NULL;

	

	//SDL_Window *wnd = NULL;
	//SDL_Renderer *renderer = NULL;
	//SDL_Texture *img = NULL;





	int imgH = 200* 4;
	int imgW = 200* 4;

	float x = 100.f;
	float y = 100.f;





	bool running = true;

	Uint64 previousTicks = SDL_GetPerformanceCounter();

	
	



	

	//window = SDL_CreateWindow("keke.bmp", 100, 100, WIDTH, HEIGHT,0);
	//render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//We need render to render stuff
	//img = IMG_LoadTexture(render, "keke.bmp");

	//SDL_QueryTexture(img, NULL, NULL, &imgW, &imgH);

	//SDL_Rect texr; texr.x = WIDTH/2; texr.y = HEIGHT/2; texr.w = imgW * 5; texr.h = imgH * 5;//Destination rectangle

	//SDL_Rect src{0,0,imgW,imgH};//image data, from where i want the image to be.
	//SDL_Rect dst {400,100,imgW,imgH};//x, y on the window from the top left corner
	/*

	while (1)
	{

		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
		}


		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, img, &src, &dst);

		
		
		SDL_SetTextureColorMod(img,rand(), rand(), rand());


		//SDL_SetRenderDrawColor(renderer, rand(), rand(), rand(), 1);
		SDL_RenderPresent(renderer);

		



	}
	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(img);
	SDL_DestroyWindow(wnd);

	*/
	

	
	while (running)
	{

		//get the delta time esque number, and  then the nextframe do it again, compare the numbers, and see how many ticks of this performance counter happened between those two frames. 
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 deltaTicks = ticks - previousTicks;
		previousTicks = ticks;

		delta_time = (float)deltaTicks / SDL_GetPerformanceFrequency();

		printf("FPS %f\n", 1.f / delta_time);

		SDL_Event event;
		while (SDL_PollEvent(&event))//puuting if here works, but then it only reads one event while using the while keeps handling more than one event in the queue?
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_ESCAPE)
					running = false;

				keys[scancode] = true;//Sets the specific key bool to true, depending on the key we press.

				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;
				keys[scancode] = false;

				break;
			}
			}

		}


		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);
		

		player.update();
		player.draw();

		for (int i = 0; i < PROJECTILE_MAX; i++)
		{
			projectiles[i].update();
			projectiles[i].draw();
		}


	
		for (int i = 0; i < BRICK_COLUMNS; i++)
		{
			for (int j = 0; j < BRICK_ROWS; j++)
			{
				bricks[i][j].x = bricks[i][j].w * i + bricks[i][j].w * 1.5;//30 here is the distance from the left side of the screen, while the bricks.w is the distance between the bricks
				bricks[i][j].y = bricks[i][j].h * j + bricks[i][j].h * 1.5;//30 here is the distance from the left side of the screen, while the bricks.w is the distance between the bricks
			}
		}
		

		for (int i = 0; i < BRICK_COLUMNS ; i++)
		{
			for (int j = 0; j < BRICK_ROWS; j++)
			{
				
				if (i == 0 && j == 0)
				{
					bricks[i][j].breakable = false;
				}
				if (i == BRICK_COLUMNS-1 && j == 0)
				{
					bricks[i][j].breakable = false;
				}
				if (i == 0 && j == BRICK_ROWS-1)
				{
					bricks[i][j].breakable = false;
				}
				if (i == BRICK_COLUMNS-1 && j == BRICK_ROWS-1)
				{
					bricks[i][j].breakable = false;
				}
				bricks[i][j].draw();
			}
		}
		for (int i = 1; i <= BRICK_COLUMNS-2; i++)
		{
			for (int j = 1; j < BRICK_ROWS-1; j++)
			{
				bricks[i][j].strongWall = true;
			}
		}
		


		



		/*AABB a = AABB::make_from_position_size(player.x, player.y, 64, 64);
		draw_box(a);*/


		/*Circle a = {player.x,player.y,32};
		draw_circle(a);

		/*if (circle_intersect(a, b))
		{
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		}
		else
		{

			SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
		}

		
		draw_circle(b);*/

		/*
		Circle AC = { player.x, player.y, 100 };

		AABB ab;
		//AABB a = AABB::make_from_position_size(player.x, player.y,50, 50);
		AABB b = AABB::make_from_position_size(600, 200, 150, 25);
		
		if (aabb_circle_intersect(b,AC))
		{

			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		}
		else
		{

			SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
		}

		/*if (aabb_intersect(a, b))
		{
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
		}*/
		/*
		draw_box(a);
		draw_box(b);
		draw_circle(AC);
		*/

		SDL_RenderPresent(render);

		//SDL_SetRenderDrawColor(render, 255,0,0, 255);//Set color and then draw, needs to be infront of every draw call, bitwise randing,  & 0xFF. rand gives us big number, whatever the byte part is 
		
		//SDL_Rect rect = {x,y,64,64};

		//SDL_RenderFillRect(render,&rect);

		//Present the renderer from the backbuffer.

		SDL_Delay(16);

		if (player.playerLives <= 0)
		{
			SDL_Quit();
			running = false;
		}
	}
	return 0;

}