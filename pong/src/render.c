#include "render.h"



//draw player to surface
void draw_player(SDL_Surface* surface, Player* player) {
	SDL_Rect player_rect = (SDL_Rect) {player->x, player->y, player->w, player->h};
	SDL_FillRect(surface, &player_rect, player->color);
	//printf("_INITPLAYER DRAWN!\n");
}

//checks every pixel in the rectangle
//if the distance from the center of the rect to the pixel < radius of the ball
//fill in the pixel
void draw_ball(SDL_Surface* surface, Ball ball) {
	//printf("ball!\n");
	for (double x=ball.x-ball.r; x<ball.x+ball.r; x++) {
		for (double y=ball.y-ball.r; y<ball.y+ball.r; y++) {
			double distance = sqrt(pow((ball.x-x), 2)+pow((ball.y-y), 2));
			//printf("Distance: %f\n", distance);
			if (distance < ball.r) {
				SDL_Rect pixel =(SDL_Rect){x, y, 1, 1};
				SDL_FillRect(surface, &pixel, ball.color);
			}
		}
	}
}

//draw score to the top of the screen
void draw_score(SDL_Surface* surface, TTF_Font* font, Player player1, Player player2) {
	char scoreText[20];
	// snprintf -> formats a string and stores it in a character array
	// syntax: snprintf(char *str, size_t size, const char *format, ...);
	snprintf(scoreText, sizeof(scoreText), "%d : %d", player1.score, player2.score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText, TEXT_COLOR);
	SDL_Rect textRect = (SDL_Rect){WIDTH/2-50, 20, 100, 40};		
	SDL_BlitSurface(textSurface, NULL, surface, &textRect);
	SDL_FreeSurface(textSurface);	
}


//countdown before game starts
void countdown(SDL_Surface* surface, SDL_Window* window, TTF_Font* font) {
	char countdownText[2];
	SDL_Rect textRect = (SDL_Rect){WIDTH/2, HEIGHT/2, 100, 100};
	for (int i=3; i>0; i--) {
		snprintf(countdownText, sizeof(countdownText), "%d", i);
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, countdownText, TEXT_COLOR);
		SDL_FillRect(surface, &textRect, COLOR_BLACK);
		SDL_BlitSurface(textSurface, NULL, surface, &textRect);
		SDL_UpdateWindowSurface(window);
		SDL_FreeSurface(textSurface);
		SDL_Delay(1000);
	}
}


//render players, ball, score - to be called during game loop
void draw_frame(SDL_Surface* surface, SDL_Window* window, Player* player1, Player* player2, Ball* ball, TTF_Font* font) {
	clear_screen(surface);
	draw_player(surface, player1);
	draw_player(surface, player2);
	draw_ball(surface,*ball);
	draw_score(surface, font, *player1, *player2);
	SDL_UpdateWindowSurface(window);
	//printf("RENDER!\n");
}

