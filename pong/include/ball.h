#ifndef BALL_H
#define BALL_H

#include "window.h"
#include "player.h"


#define BALL_SPEED 10
#define BALL_SIZE 15
#define COLOR_WHITE 0xffffffff

typedef struct {
	double x, y, r, v_x, v_y;
  Uint32 color;
} Ball;

void init_ball(Ball* ball);
void step(SDL_Surface* surface, Ball* ball, Player* players[]);


#endif
