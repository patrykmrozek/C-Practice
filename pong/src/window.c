#include "window.h"

//create window
SDL_Window* init_window() {	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);
	return window;
}

//get surface
SDL_Surface* get_surface(SDL_Window* window) {
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	return surface;
}

//fetch and load font
TTF_Font* load_font() {
	//initialize TTF, check for errors
	if (TTF_Init() == -1) {
		printf("TTF Initialization Failed: %s/n", TTF_GetError());
		return NULL;
	};
	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 25);
	if (!font) {
		printf("font not loaded\n");
	}
	return font;
}
