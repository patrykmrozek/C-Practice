#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define GRAVITY 1.98
#define DAMPEN 1
#define NUM_CIRCLES 2
#define COLOR_RED 0x00ff0000
struct Circle {
	double x;
	double y;
	double r;
	double v_x;
	double v_y;
};


void draw_circle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
	
	for (double x=circle.x-circle.r; x<circle.x+circle.r; x++) {
		for (double y=circle.y-circle.r; y<circle.y+circle.r; y++) {
			double distance = sqrt(pow((circle.x-x), 2)+pow((circle.y-y), 2));
			//printf("Distance: %f\n", distance);
			if (distance < circle.r) {
				SDL_Rect pixel =(SDL_Rect){x, y, 1, 1};
				SDL_FillRect(surface, &pixel, color);
			}
		}
	}	
}


void step(struct Circle* circle){ //parameter is a pointer to the struct

	//draw_circle(surface, circle, color);
	//printf("X: %f - Y: %f\n", circle -> x, circle -> y);
	if (circle->x+circle->r > WIDTH) {
		circle->v_x = -circle->v_x;
		circle->v_x += DAMPEN;
		circle->x = WIDTH-circle->r;
	}
	if (circle->x-circle->r < 0) {
		circle->v_x = -circle->v_x;
		circle->v_x -= DAMPEN;
		circle->x = circle->r; 
	}
	if (circle->y+circle->r > HEIGHT) {
		circle->v_y = -circle->v_y;
		circle->v_y += DAMPEN;
		circle->y = HEIGHT-circle->r;
	}
	if (circle->y-circle->r < 0) {
		circle->v_y = -circle->v_y;
		circle->v_y -= DAMPEN;
		circle->y = circle->r;
	}
	circle->x += circle->v_x;
	circle->y += circle->v_y += GRAVITY;
}


int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN
	);
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);	
	if (!window) {
		printf("NO WINDOW\n");
	}

	SDL_RaiseWindow(window);
	SDL_PumpEvents();//force an event queue update to show window
	
	struct Circle circle1={100, HEIGHT-10, 30, -30, 60};
	struct Circle circle2={20, 20, 40, 20, 15};
	struct Circle circles[] = {circle1, circle2}; 
	SDL_Rect erase = (SDL_Rect){0, 0, WIDTH, HEIGHT};
	SDL_Event event;
	int running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type==SDL_QUIT) {
				running=0;
			}
			if (event.type == SDL_MOUSEMOTION) {
				//printf("mouse event\n");
				
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					printf("SPACE\n");
				}
			}
		}
		
		SDL_FillRect(surface, &erase, COLOR_BLACK);
		for (int i=0; i<NUM_CIRCLES; i++) {
			//printf("CIRCLE\n");
			draw_circle(surface, circles[i], COLOR_WHITE);
			step(&circles[i]);
		}
	
		SDL_UpdateWindowSurface(window);
		SDL_Delay(20);
		//printf("X VELOCITY: %f\tY VELOCITY: %f\n", circle.v_x, circle.v_y);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}





