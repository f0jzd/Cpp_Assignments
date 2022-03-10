#include "camera.h"
#include "game.h"

void Camera::update()
{
	x = player.x - 900;
	y = player.y - 450;

};