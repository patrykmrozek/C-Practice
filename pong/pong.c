#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>

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
#define BALL_SIZE 15


typedef struct {
	double x, y, w, h;
	int score;
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
	ball->v_y = (rand()%2==0 ? BALL_SPEED/2 : -BALL_SPEED/2);
	SDL_Delay(1000);
	printf("PLAYER 1: %d\nPLAYER 2: %d\n\n", p1->score, p2->score);
}

void step(Circle* circle, Player* players[]){
	if (circle->x > WIDTH) {
		reset(circle, players[0], players[1]);
		players[0]->score++;
	} else if (circle->x < 0) {
		reset(circle, players[0], players[1]);
		players[1]->score++;
	}
	for (int i=0; i<2; i++){
		if (check_collision(circle, players[i])) {
			circle->v_x = -circle->v_x;
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
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	
	TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 24);
	if (!font) {
		printf("font not loaded\n");
	}
		SDL_RaiseWindow(window);
	SDL_PumpEvents();
	Player player1 = {
		PLAYER_1_X-(PLAYER_W/2),
		PLAYER_1_Y-(PLAYER_H/2),
		PLAYER_W,
		PLAYER_H,
		0
	};
	Player player2 = {
		PLAYER_2_X-(PLAYER_W/2),
		PLAYER_2_Y-(PLAYER_H/2),
		PLAYER_W,
		PLAYER_H,
		0
	};
	SDL_Color text_color = {255, 255, 255, 255};

	Player* players[] = {&player1, &player2};
	
	Circle circle = {WIDTH/2, HEIGHT/2, BALL_SIZE, BALL_SPEED, BALL_SPEED};
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
		
		char score_text[20];
		// snprintf -> formats a string and stores it in a character array
		// syntax: snprintf(char *str, size_t size, const char *format, ...);
		snprintf(score_text, sizeof(score_text), "%d : %d", player1.score, player2.score);
		SDL_Surface* text_surface = TTF_RenderText_Solid(font, score_text, text_color);
		SDL_Rect text_rect = (SDL_Rect){WIDTH/2-50, 20, 100, 40};	


	
		SDL_FillRect(surface, &erase, COLOR_BLACK);
		SDL_BlitSurface(text_surface, NULL, surface, &text_rect);
		draw_player(surface, &player1);
		draw_player(surface, &player2);
		draw_circle(surface, circle, COLOR_WHITE);
		step(&circle, players);
		SDL_UpdateWindowSurface(window);
		SDL_Delay(16); //approx 60 fps
		
		SDL_FreeSurface(text_surface);
	}
	SDL_Quit();
	SDL_DestroyWindow(window);
	return 0;
	
}

