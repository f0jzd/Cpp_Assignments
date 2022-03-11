#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "engine.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include <string>
#include "main.h"
#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

#define WIDTH 1600
#define HEIGHT 900
#define IMG_PATH "cow.png"


SDL_Surface* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gPNGSurface = NULL;


SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);

	SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
}



class Levels
{
	std::vector<vector<int>> arrOfLevels;

public:
	void AddToVector(std::vector<int> lvl)
	{
		arrOfLevels.push_back(lvl);
	}

	vector<int> GetLevel(int index)
	{
		return arrOfLevels[index];
	}
};


void UpdateProjectiles()
{
	for (int i = 0; i < PROJECTILE_MAX; i++)
	{
		if (projectiles[i].alive)
		{

			projectiles[i].update();
			projectiles[i].draw();

				
		}		
	}
}

vector<int> GetLevel()
{
	vector<int> theLevel;
	string levels;
	bool levelSelected = false;
	int selectedLevel = 1;
	char a;
	int numberOfLines = 0;

	

	fstream infile("levels.txt", fstream::in);

	while (std::getline(infile, levels))
		++numberOfLines;

	infile.clear();
	infile.seekg(0);


	//cout << "Choose your level: ";
	//cin >> selectedLevel;

	/*while (selectedLevel>numberOfLines && !levelSelected)
	{

		if(selectedLevel<numberOfLines)
		{
			levelSelected = true;
		}
		else
		{
			cout << "That level does not exist";
			cin >> selectedLevel;
		}

		
	}*/

	for (int i = 0; i <= selectedLevel; ++i)
	{
		getline(infile, levels);
	}
		


	getline(infile, levels);

	for (auto value : levels)
	{
		if (std::isdigit(value))
		{
			int ia = value - '0';
			theLevel.push_back(ia);
		}
	}

	/*infile.clear();
	infile.seekg(0);

	getline(infile, levels);*/

	infile.close();

	return theLevel;
}


void drawSprites(SDL_Texture* img, int imgH, int imgW, int frame, SDL_Texture* img2)
{
	for (int i = 0; i < BRICK_COLUMNS ; i++)
	{
		for (int j = 0; j < BRICK_ROWS; j++)
		{
			//EditBrick(i, j);
			if (bricks[i][j].alive)
			{
				SDL_SetTextureColorMod(img, rand(), rand(), rand());
				SDL_Rect src{ frame*imgW,0,imgW,imgH };//image data, from where i want the image to be.
				SDL_Rect dst{ bricks[i][j].x - 80,bricks[i][j].y - 30,bricks[i][j].w,bricks[i][j].h };//x, y on the window from the top left corner
				SDL_RenderCopy(render, img2, &src, &dst);
			}				
			bricks[i][j].draw();
		}
	}
}

void SetBrickType(vector<int> lvl1, int l)
{
	for (int i = 0; i < BRICK_ROWS; i++)
	{
		for (int j = 0; j < BRICK_COLUMNS; j++)
		{
			if (lvl1[l] == 0)
			{
				bricks[j][i].breakable = false;
			}
			if (lvl1[l] == 2)
			{
				bricks[j][i].strongWall = true;
			}
			if (lvl1[l] == 3)
			{
				bricks[j][i].alive = false;
			}
			l++;
		}
	}
}

int main()
{


	SDL_Init(SDL_INIT_EVERYTHING);//Initialize the usage of everything
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0); //A structure to refer to the window we just made
	render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_Texture* img = NULL;
	int imgflags = IMG_INIT_PNG;

	TTF_Init();

	TTF_Font* roboto = TTF_OpenFont("roboto.ttf",90);
	if (!roboto)
	{
		cout << "Something went Wrong";
	}
	
	SDL_Color white = { 255,255,255,255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(roboto, "Hello", white);
	SDL_Texture* message = SDL_CreateTextureFromSurface(render, surfaceMessage);
	SDL_Rect message_rect;

	message_rect.x = 0;
	message_rect.y = 0;
	message_rect.w = 100;
	message_rect.h = 100;

	


	//SDL_Surface* surfaceMessage = 

	SDL_Surface* gScreenSurface = SDL_GetWindowSurface(window);

	int imgH = 112;
	int imgW = 112;
	int frame = 0;

	float frameTimer = 0.f;

	bool running = true;

	Uint64 previousTicks = SDL_GetPerformanceCounter();

	auto img2 = IMG_LoadTexture(render, IMG_PATH);

	IMG_Init(IMG_INIT_PNG);


	vector<int> lvl1 = {
	};


	lvl1 = GetLevel();

	
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

		UpdateProjectiles();

		
		int xPos, yPos;
		SDL_PumpEvents();
		Uint32 buttons = SDL_GetMouseState(&xPos, &yPos);
		message_rect.x = xPos - 50;
		message_rect.y = yPos - 50;
		SDL_RenderCopy(render, message, NULL, &message_rect);
		

		//wall[0].y = 0 + wall[0].h / 2;

		for (int i = 0; i < 4; i++)
		{
			wall[i].y = wall[i].h * i + wall[i].h / 2;
			
		};


		for (int i = 0; i < 4; i++)
		{
			wall[i].draw();
		}


	
		for (int i = 0; i < BRICK_COLUMNS; i++)
		{
			for (int j = 0; j < BRICK_ROWS; j++)
			{
				bricks[i][j].x = bricks[i][j].w * i + bricks[i][j].w * 1.5;//30 here is the distance from the left side of the screen, while the bricks.w is the distance between the bricks
				bricks[i][j].y = bricks[i][j].h * j + bricks[i][j].h * 1.5;//30 here is the distance from the left side of the screen, while the bricks.w is the distance between the bricks
			}
		}

		int l = 0;

		SetBrickType(lvl1, l);

		drawSprites(img, imgH, imgW, frame, img2);






		/*bricks[7][4].breakable = false;
		bricks[7][4].x = xPos;
		bricks[7][4].y = yPos;

		SDL_Rect src{ frame * imgW,0,imgW,imgH };
		SDL_Rect dst{ bricks[7][4].x - 80,bricks[7][4].y - 30,bricks[7][4].w, bricks[7][4].h };
		
		bricks[7][4].draw();
		SDL_RenderCopy(render, img2, &src, &dst);*/

		//SetStrongwalls();

		frameTimer -= delta_time;

		if (frameTimer < 0)
		{
			frame++;
			frameTimer = 0.04545454545;
			FrameReset(frame);
		}




		//SDL_RenderDrawLine(render, player.x + player.playerWidth / 2, player.y - player.playerHeight/2, projectiles[0].x, projectiles[0].y);



		// Don't forget to free your surface and texture
		

		SDL_RenderPresent(render);


		SDL_Delay(16);

		if (player.playerLives <= 0)
		{
			SDL_Quit();
			running = false;
		}
	}
	return 0;

}



void EditBrick(int i, int j)
{
	if (i == 0 && j == 0)
	{
		bricks[i][j].breakable = false;
	}
	if (i == BRICK_COLUMNS - 1 && j == 0)
	{
		bricks[i][j].breakable = false;
	}
	
	if (i == BRICK_COLUMNS - 1 && j == BRICK_ROWS - 1)
	{
		bricks[i][j].breakable = false;
	}
}

void FrameReset(int& frame)
{
	if (frame == 21)
	{
		frame = 0;
	}
}
