#pragma once

struct Projectile
{
	bool alive = false;

	float x;
	float y;

	int velocity_x;
	int velocity_y;



	void update();
	void draw();

	bool step(float dx, float dy);
};
