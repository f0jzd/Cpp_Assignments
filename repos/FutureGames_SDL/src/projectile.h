#pragma once

struct Projectile
{
	bool alive = false;

	float x;
	float y;

	float velocity_x;
	float velocity_y;
	float speed{500};



	void update();
	void draw();

	bool step(float dx, float dy);
};
