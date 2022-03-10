#pragma once


struct Player
{
	float x{ 100.f };
	float y{ 100.f };

	float velocityX{100.f};
	float velocityY{0.f};


	int playerLives = 3;

	int playerMovementspeed = 500;

	float shoot_timer = 0.f;

	int next_projectile_index = 0;

	int playerWidth{ 64 };
	int playerHeight{ 8 };

	bool ballFired = false;

	bool step(float dx, float dy);
	bool sweep(float dx, float dy);



	void update();
	void CheckMovement();
	void draw();
	void DrawBall();
};