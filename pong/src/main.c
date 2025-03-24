#include <stdio.h>
#include <math.h>
#include "game.h"
#include "ball.h"
#include "window.h"
#include "render.h"
#include "menu.h"
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
	//countdown(surface, window, font);
	SDL_Event event;
	int programRunning = 1;
	int gamePlaying = 0;

  while (programRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || gamePlaying == 2) {
				programRunning = 0;
			}
		}

      if (gamePlaying == 1) {
    //	printf("CIRCLE X: %f, Y: %f\n", circle.x, circle.y);
       input_handle(&player1, &player2, window, &programRunning);
       step(surface, &ball, players);
       in_bounds(players);
       draw_frame(surface, window, &player1, &player2, &ball, font);
       SDL_Delay(16); //approx 60 fps
	
    } else {
        gamePlaying = draw_menu(surface, window, event, font);
        //printf("GAMEPLAYING: %d\n", gamePlaying);
      //printf("paused");
      //SDL_Delay(1000);
    }
  }
	shutdown(window);	
}

