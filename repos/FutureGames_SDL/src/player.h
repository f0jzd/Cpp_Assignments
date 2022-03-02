#pragma once


struct Player
{
	float x{ 100 };
	float y{100 };

	float shoot_timer = 0.f;

	int next_projectile_index = 0;

	void update();
	void draw();
};