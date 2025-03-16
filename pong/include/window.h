#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 1000
#define HEIGHT 700

SDL_Window* init_window();
SDL_Surface* get_surface(SDL_Window* window);
TTF_Font* load_font();

#endif
