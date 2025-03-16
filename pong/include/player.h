#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#define COLOR_WHITE 0xffffffff
#define SPEED 10
#define WIDTH 1000
#define HEIGHT 700
#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 60
#define PLAYER_1_X_INIT WIDTH/8
#define PLAYER_1_Y_INIT HEIGHT/2
#define PLAYER_2_X_INIT (WIDTH/8)*7
#define PLAYER_2_Y_INIT HEIGHT/2



typedef struct {
	double x, y, w, h;
	int score;
  Uint32 color;
} Player;


void init_players(Player* player1, Player* player2);
void in_bounds(Player* players[]);


#endif
