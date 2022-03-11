#pragma once

struct Wall
{
	float h = 160.f;
	float w = 60.f;

	float x = 1600;//x-width/2
	float y = 0; //y+height/2

	void draw();
};