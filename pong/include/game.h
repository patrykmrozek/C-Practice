#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "ball.h"
#include "player.h"

#define COLOR_BLACK 0x00000000

void reset_ball(Ball* ball);
void reset_players(Player* player1, Player* player2);
int check_collision(Ball* ball, Player* player);
void clear_screen(SDL_Surface* surface);
int shutdown(SDL_Window* window);
void input_handle(Player* player1, Player* player2, SDL_Window* window, int* programRunning, int* gamePlaying);


#endif
