#include <stdio.h>
#include <math.h>
#include "game.h"
#include "ball.h"
#include "window.h"
#include "render.h"
//function prototypes - independant ordering, more readable

int main() {
	SDL_Window* window = init_window();
	SDL_Surface* surface = get_surface(window);
	TTF_Font* font = load_font();
	
	Player player1, player2;
	init_players(&player1, &player2);
	
	Ball ball;
	init_ball(&ball);	
	reset_ball(&ball);
	//printf("CIRCLE: %f, %f", circle.x, circle.y);
	
	SDL_RaiseWindow(window);
	SDL_PumpEvents();

	Player* players[] = {&player1, &player2};
	countdown(surface, window, font);
	SDL_Event event;
	int programRunning = 1;
	while (programRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				programRunning = 0;
			}
		}
	//	printf("CIRCLE X: %f, Y: %f\n", circle.x, circle.y);
		input_handle(&player1, &player2, window, &programRunning);
		step(surface, &ball, players);
		in_bounds(players);
		draw_frame(surface, window, &player1, &player2, &ball, font);
		SDL_Delay(16); //approx 60 fps
	}
	shutdown(window);	
}

