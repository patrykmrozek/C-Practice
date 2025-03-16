#include "game.h"
#include "player.h"
#include "ball.h"


//resets player positions
void reset_players(Player* p1, Player* p2) {
	p1->x = PLAYER_1_X_INIT;
	p1->y = PLAYER_1_Y_INIT;
	p2->x = PLAYER_2_X_INIT;
	p2->y = PLAYER_2_Y_INIT;	
	
	//printf("PLAYER 1: %d\nPLAYER 2: %d\n\n", p1->score, p2->score);
}

//resets ball position and generates random x and y velocities for the ball
void reset_ball(Ball* ball) {
	ball->x = WIDTH/2;
	ball->y = HEIGHT/2;
	// rand()%2 generates a random num between 0 and 1
	// randomly assigns the balls' v_x and v_y
	ball->v_x = (rand()%2==0 ? BALL_SPEED: -BALL_SPEED);
	ball->v_y = (rand()%2==0 ? BALL_SPEED/2 : -BALL_SPEED/3);
}

// will return TRUE(1) if ball collides with player
int check_collision(Ball* ball, Player* player) {
	return (ball->x+ball->r > player->x &&
		ball->x-ball->r < player->x+player->w &&
		ball->y+ball->r > player->y &&
		ball->y-ball->r < player->y+player->h);
}

//draw black rectangle the size of the screen
void clear_screen(SDL_Surface* surface) {
	SDL_Rect erase = {0, 0, WIDTH, HEIGHT};
	SDL_FillRect(surface, &erase, COLOR_BLACK);
}

//destroys window and quits SDL
int shutdown(SDL_Window* window) {
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

//handle user inputs
void input_handle(Player* player1, Player* player2, SDL_Window* window, int* programRunning) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W]) player1->y -= SPEED;
	if (keystate[SDL_SCANCODE_S]) player1->y += SPEED;
	if (keystate[SDL_SCANCODE_UP]) player2->y -= SPEED;
	if (keystate[SDL_SCANCODE_DOWN]) player2->y += SPEED;		
	if (keystate[SDL_SCANCODE_Q]) *programRunning = 0;
}
