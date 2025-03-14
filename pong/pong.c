#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 700
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define PLAYER_W 20
#define PLAYER_H 60
#define PLAYER_1_X WIDTH/8
#define PLAYER_1_Y HEIGHT/2
#define PLAYER_2_X (WIDTH/8)*7
#define PLAYER_2_Y HEIGHT/2
#define SPEED 10
#define BALL_SPEED 10

typedef struct {
	double x, y, w, h;
} Player;


typedef struct {
	double x, y, r, v_x, v_y;
} Circle;


void draw_player(SDL_Surface* surface, Player* player) {
	SDL_Rect player_rect = (SDL_Rect) {player->x, player->y, player->w, player->h};
	SDL_FillRect(surface, &player_rect, COLOR_WHITE);
	//printf("PLAYER DRAWN!\n");
}

// will return TRUE(1) if ball collides with player
int check_collision(Circle* ball, Player* player) {
	return (ball->x+ball->r > player->x &&
		ball->x-ball->r < player->x+player->w &&
		ball->y+ball->r > player->y &&
		ball->y-ball->r < player->y+player->h);
}

void in_bounds(Player* players[]) {
	for (int i=0; i<2; i++) {
		if (players[i]->y >= HEIGHT-players[i]->h) {
			players[i]->y = HEIGHT-players[i]->h;
		} else if (players[i]->y <= 0 ) {
			players[i]->y = 0;
		}	
	}
	//printf("PLAYER Y: %f\n", player->y);
}

void draw_circle(SDL_Surface* surface, Circle circle, Uint32 color) {

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

void reset(Circle* ball, Player* p1, Player* p2) {
	p1->x = PLAYER_1_X;
	p1->y = PLAYER_1_Y;
	p2->x = PLAYER_2_X;
	p2->y = PLAYER_2_Y;	
	
	ball->x = WIDTH/2;
	ball->y = HEIGHT/2;
	// rand()%2 generates a random num between 0 and 1
	// randomly assigns the balls' v_x and v_y
	ball->v_x = (rand()%2==0 ? BALL_SPEED: -BALL_SPEED);
	ball->v_y = (rand()%2==0 ? BALL_SPEED : -BALL_SPEED);
	SDL_Delay(1000);
}

void step(Circle* circle, Player* players[], int* score1, int* score2){
	if (circle->x > WIDTH) {
		reset(circle, players[0], players[1]);
		(*score2)++;
	} else if (circle->x < 0) {
		reset(circle, players[0], players[1]);
		(*score1)++;
	}
	for (int i=0; i<2; i++){
		if (check_collision(circle, players[i])) {
			circle->v_x = -circle->v_x;
			//adjusts angle of the ball based on where it was hit
			double offset = (circle->y - ((players[i]->y + players[i]->h/2)
					/players[i]->h/2));
			circle->v_y = offset*BALL_SPEED;
		}
	}
	if (circle->y <= 0 || circle->y >= HEIGHT - circle->r) {
		circle->v_y = -circle->v_y;
	}
	circle->x += circle->v_x;
	circle->y += circle->v_y;
}

void input_handle(Player* player1, Player* player2) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W]) player1->y -= SPEED;
	if (keystate[SDL_SCANCODE_S]) player1->y += SPEED;
	if (keystate[SDL_SCANCODE_UP]) player2->y -= SPEED;
	if (keystate[SDL_SCANCODE_DOWN]) player2->y += SPEED;		
}

int main() {

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	
	SDL_RaiseWindow(window);
	SDL_PumpEvents();
	Player player1 = {
		PLAYER_1_X-(PLAYER_W/2),
		PLAYER_1_Y-(PLAYER_H/2),
		PLAYER_W,
		PLAYER_H
	};
	Player player2 = {
		PLAYER_2_X-(PLAYER_W/2),
		PLAYER_2_Y-(PLAYER_H/2),
		PLAYER_W,
		PLAYER_H
	};
	
	Player* players[] = {&player1, &player2};
	
	int score1=0, score2=0;

	Circle circle = {WIDTH/2, HEIGHT/2, 15, BALL_SPEED, 2};
	reset(&circle, &player1, &player2);
	SDL_Rect erase = (SDL_Rect){0, 0, WIDTH, HEIGHT};
	SDL_Event event;
	int program_running = 1;
	while (program_running) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				program_running = 0;
			}
		}

		input_handle(&player1, &player2);
		in_bounds(players);
			
		SDL_FillRect(surface, &erase, COLOR_BLACK);
		draw_player(surface, &player1);
		draw_player(surface, &player2);
		draw_circle(surface, circle, COLOR_WHITE);
		step(&circle, players, &score1, &score2);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(16); //approx 60 fps
		printf("SCORE1: %d\nSCORE2: %d\n", score1, score2);
	}
}
