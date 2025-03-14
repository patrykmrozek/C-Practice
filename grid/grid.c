#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#define HEIGHT 700
#define WIDTH 1000
#define CELL_SIZE 10
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_GREY 0x50505050
#define LINE_WIDTH 1

void draw_grid(SDL_Surface* surface) {
	for (int i=0; i<WIDTH; i++) {
		SDL_Rect *col = (SDL_Rect){0, (CELL_SIZE*i), WIDTH, LINE_WIDTH};
		SDL_FillRect(surface, col, COLOR_GREY);
	}
	for (int i=0; i<HEIGHT; i++) {
		SDL_Rect *row = (SDL_Rect){(CELL_SIZE*i), 0, LINE_WIDTH, HEIGHT};
		SDL_FillRect(surface, row, COLOR_GREY);
	}
}

void draw_cell(SDL_Surface* surface, int mouse_x, int mouse_y) {
	SDL_Rect* cell = (SDL_Rect){
			(mouse_x*CELL_SIZE),
			(mouse_y*CELL_SIZE),
			CELL_SIZE,
			CELL_SIZE};
	SDL_FillRect(surface, cell, COLOR_WHITE);
}

int main() {

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"GRID",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_RaiseWindow(window);
	SDL_Rect erase = (SDL_Rect){0, 0, WIDTH, HEIGHT};
	SDL_PumpEvents();
	draw_grid(surface);
	SDL_UpdateWindowSurface(window);
	
	int program_running = 1;
	SDL_Event event;
	while (program_running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				program_running = 0;
			}
			if (event.type == SDL_MOUSEMOTION) {
				if (event.motion.state != 0) {
					//printf("STATE: %d\n", event.motion.state);
					//printf("X: %d - Y: %d\n", event.motion.x, event.motion.y);
					int mouse_x = event.motion.x/CELL_SIZE;
					int mouse_y = event.motion.y/CELL_SIZE;
					draw_cell(surface, mouse_x, mouse_y);
					//SDL_UpdateWindowSurface(window);
				}
			}
			if (event.type == SDL_KEYDOWN) {	
				printf("KEY PRESSED \n");
				if (event.key.keysym.sym == SDLK_BACKSPACE){
					SDL_FillRect(surface, &erase, COLOR_BLACK);
					draw_grid(surface);
				}		
			}
			
		}
	}
	SDL_UpdateWindowSurface(window);		
	SDL_Delay(10);

	return 0;

}
