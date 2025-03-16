#ifndef RENDER_H
#define RENDER_H
#include "game.h"
#include "player.h"
#include "ball.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>


#define TEXT_COLOR (SDL_Color){255, 255, 255, 255}
#define COLOR_BLACK 0x00000000

void draw_player(SDL_Surface* surface, Player* player);
void draw_ball(SDL_Surface* surface, Ball ball);
void draw_score(SDL_Surface* surface, TTF_Font* font, Player player1, Player player2);
void countdown(SDL_Surface* surface, SDL_Window* window, TTF_Font* font);
void draw_frame(SDL_Surface* surface, SDL_Window* window, Player* player1, Player* player2, Ball* ball, TTF_Font* font);
#endif

