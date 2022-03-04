#pragma once


struct Player
{
	float x{ 800 };
	float y{ 800 };

	float shoot_timer = 0.f;

	int next_projectile_index = 0;

	void update();
	void draw();
};