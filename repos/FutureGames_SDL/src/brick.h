#pragma once


struct Brick
{

	bool alive = true;
	
	float w = 160.f;
	float h = 60.f;

	float x = 0;//x-width/2
	float y = 0; //y+height/2
	

	void draw();
	
};