#pragma once
#include "player.h"
#include "projectile.h"
#include "brick.h"

#define PROJECTILE_MAX 20
#define BRICK_MAX 8

extern Player player;//Stack the plaeyr, put him in stack
extern Projectile projectiles[PROJECTILE_MAX];
extern Brick bricks[BRICK_MAX];

