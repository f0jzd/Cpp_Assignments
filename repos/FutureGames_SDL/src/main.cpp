#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

#define WIDTH 1600
#define HEIGHT 900

#define IMG_PATH "image.png"

int main()
{
	//printf("Emil is the man\n");

	//SDL_Init(SDL_INIT_EVERYTHING);//Initialize the usage of everything
	/*SDL_Window* wnd = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0); //A structure to refer to the window we just made
	SDL_Renderer* renderer = SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED);
	SDL_Texture* img = NULL;*/

	SDL_Window *wnd = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;




	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

	}

	int imgH = 200* 4;
	int imgW = 200* 4;

	float x = 100.f;
	float y = 100.f;

	bool pressingW=false;
	bool pressingA=false;
	bool pressingS=false;
	bool pressingD=false;

	bool running = true;

	Uint64 previousTicks = SDL_GetPerformanceCounter();





	

	wnd = SDL_CreateWindow("keke.bmp", 100, 100, WIDTH, HEIGHT,0);
	renderer = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	img = IMG_LoadTexture(renderer, "keke.bmp");

	//SDL_QueryTexture(img, NULL, NULL, &imgW, &imgH);

	//SDL_Rect texr; texr.x = WIDTH/2; texr.y = HEIGHT/2; texr.w = imgW * 5; texr.h = imgH * 5;//Destination rectangle

	SDL_Rect src{0,0,imgW,imgH};//image data, from where i want the image to be.
	SDL_Rect dst {400,100,imgW,imgH};//x, y on the window from the top left corner


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


	

	
	/*while (running)
	{

		//get the delta time esque number, and  then the nextframe do it again, compare the numbers, and see how many ticks of this performance counter happened between those two frames. 
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 deltaTicks = ticks - previousTicks;
		previousTicks = ticks;

		float delta_Time = (float)deltaTicks / SDL_GetPerformanceFrequency();

		printf("FPS %f\n", 1.f / delta_Time);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
			{
				int scancode = event.key.keysym.scancode;
				printf("%d \n", scancode);
				if (scancode == SDL_SCANCODE_ESCAPE)
					running = false;
				if (scancode == SDL_SCANCODE_D)
					pressingD = true;
				if (scancode == SDL_SCANCODE_A)
					pressingA = true;
				if (scancode == SDL_SCANCODE_W)
					pressingW = true;
				if (scancode == SDL_SCANCODE_S)
					pressingS = true;
				break;
			}
			case SDL_KEYUP:
			{
				int scancode = event.key.keysym.scancode;
				if (scancode == SDL_SCANCODE_D)
					pressingD = false;
				if (scancode == SDL_SCANCODE_A)
					pressingA = false;
				if (scancode == SDL_SCANCODE_W)
					pressingW = false;
				if (scancode == SDL_SCANCODE_S)
					pressingS = false;
				break;
			}
			}
			

		}

		if (pressingW)
		{
			y -= 100 * delta_Time;//instead we want 100 units per second-ish logic
		}
		if (pressingA)
		{
			x -= 100 * delta_Time;
		}
		if (pressingS)
		{
			y += 100 * delta_Time;
		}
		if (pressingD)
		{
			x += 100 * delta_Time;
		}
		
		SDL_SetRenderDrawColor(renderer,25,25,40,255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255,0,0, 255);//Set color and then draw, needs to be infront of every draw call, bitwise randing,  & 0xFF. rand gives us big number, whatever the byte part is 
		
		SDL_Rect rect = {x,y,64,64};

		SDL_RenderFillRect(renderer,&rect);

		SDL_RenderPresent(renderer);//Present the renderer from the backbuffer.

		//SDL_Delay(16);
	}*/
	return 0;

}