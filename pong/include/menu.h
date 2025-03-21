#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"

#define TEXT_COLOR (SDL_Color){255, 255, 255, 255}
#define TEXT_WIDTH WIDTH/8
#define TEXT_HEIGHT HEIGHT/10

int checkMouseCollision(SDL_Event event, SDL_Rect* rect);
int draw_menu(SDL_Surface* surface, SDL_Window* window, SDL_Event event, TTF_Font* font);

#endif // !DEBUG
