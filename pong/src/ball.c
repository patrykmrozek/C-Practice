#include "ball.h"
#include "player.h"
#include "game.h"

void init_ball(Ball* ball) {
	*ball = (Ball){
		WIDTH/2,
		HEIGHT/2,
		BALL_SIZE,
		BALL_SPEED,
		BALL_SPEED,
    COLOR_WHITE
  };	
}
 

//calculates balls position for the next frame
void step(SDL_Surface* surface, Ball* ball, Player* players[]){
	//check if players are in bounds 
	in_bounds(players);

	//if ball exits on the right side of the screen
	if (ball->x > WIDTH) {
		reset_ball(ball);
		//reset_players(players[0], players[1]);
		players[0]->score++;
		SDL_Delay(1000);

	//if the ball exits on the left side of the screen
	} else if (ball->x < 0) {
		reset_ball(ball);
		//reset_players(players[0], players[1]);
		players[1]->score++;
		SDL_Delay(1000);
	}
	//check if ball collides with one of the players
	for (int i=0; i<2; i++){
		//if they do, reverse the x velocity of the ball
		if (check_collision(ball, players[i])) {
			ball->v_x = -ball->v_x;
      //ball->v_y = -(players[i]->y) / ball->v_y; 
		  ball->v_y += (ball->y - (players[i]->y + players[i]->h/2))/10; 
    }
	}
	//if ball hits off of the ceiling or the ground
	if (ball->y <= 0 || ball->y >= HEIGHT - ball->r) {
		//if it does, reverse the y velocity of the ball
		ball->v_y = -ball->v_y;
	}
	//increase the balls x and y by their velocity respectively
	ball->x += ball->v_x;
	ball->y += ball->v_y;
}




