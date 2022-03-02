#pragma once

struct Projectile
{
	bool alive = false;

	float x;
	float y;
	void update();
	void draw();
};
