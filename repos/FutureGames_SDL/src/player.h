#pragma once


struct Player
{
	float x{ 600 };
	float y{ 800 };

	int playerLives = 3;

	int playerMovementspeed = 500;

	float shoot_timer = 0.f;

	int next_projectile_index = 0;

	int playerWidth{ 32 };
	int playerHeight{ 8 };

	bool ballFired = false;

	void update();
	void draw();
	void DrawBall();
};