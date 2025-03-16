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
#define PLAYER_1_X_INIT WIDTH/8
#define PLAYER_1_Y_INIT HEIGHT/2
#define PLAYER_2_X_INIT (WIDTH/8)*7
#define PLAYER_2_Y_INIT HEIGHT/2
#define SPEED 10
#define BALL_SPEED 10
#define BALL_SIZE 15
#define TEXT_COLOR (SDL_Color){255, 255, 255, 255}

typedef struct {
	double x, y, w, h;
	int score;
  Uint32 color;
} Player;


typedef struct {
	double x, y, r, v_x, v_y;
  Uint32 color;
} Circle;

//function prototypes - independant ordering, more readable
SDL_Window* init_window();
SDL_Surface* get_surface(SDL_Window* window);
TTF_Font* load_font();
void init_players(Player* player1, Player* player2);
void init_circle(Circle* circle);
void draw_player(SDL_Surface* surface, Player* player);
void draw_circle(SDL_Surface* surface, Circle circle);
void draw_score(SDL_Surface* surface, TTF_Font* font, Player player1, Player player2);
void step(SDL_Surface* surface, Circle* circle, Player* players[]);
void reset_circle(Circle* circle);
void reset_players(Player* player1, Player* player2);
void in_bounds(Player* players[]);
void input_handle(Player* player1, Player* player2, SDL_Window* window, int* programRunning);
int check_collision(Circle* circle, Player* player);
void countdown(SDL_Surface* surface, SDL_Window* window, TTF_Font* font);
void render(SDL_Surface* surface, SDL_Window* window, Player* player1, Player* player2, Circle* circle, TTF_Font* font);
void clear_screen(SDL_Surface* surface);
int shutdown(SDL_Window* window);

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

//initialize players
void init_players(Player* player1, Player* player2) {
	*player1 = (Player) {
		PLAYER_1_X_INIT,
		PLAYER_1_Y_INIT,
		PLAYER_W,
		PLAYER_H,
		0,
    COLOR_WHITE
	};
	
	*player2 = (Player) {
		PLAYER_2_X_INIT,
		PLAYER_2_Y_INIT,
		PLAYER_W,
		PLAYER_H,
		0,
    COLOR_WHITE
	};

}

void init_circle(Circle* circle) {
	*circle = (Circle){
		WIDTH/2,
		HEIGHT/2,
		BALL_SIZE,
		BALL_SPEED,
		BALL_SPEED,
    COLOR_WHITE
  };	
}

//draw player to surface
void draw_player(SDL_Surface* surface, Player* player) {
	SDL_Rect player_rect = (SDL_Rect) {player->x, player->y, player->w, player->h};
	SDL_FillRect(surface, &player_rect, player->color);
	//printf("_INITPLAYER DRAWN!\n");
}

//checks every pixel in the rectangle
//if the distance from the center of the rect to the pixel < radius of the circle
//fill in the pixel
void draw_circle(SDL_Surface* surface, Circle circle) {
	//printf("CIRCLE!\n");
	for (double x=circle.x-circle.r; x<circle.x+circle.r; x++) {
		for (double y=circle.y-circle.r; y<circle.y+circle.r; y++) {
			double distance = sqrt(pow((circle.x-x), 2)+pow((circle.y-y), 2));
			//printf("Distance: %f\n", distance);
			if (distance < circle.r) {
				SDL_Rect pixel =(SDL_Rect){x, y, 1, 1};
				SDL_FillRect(surface, &pixel, circle.color);
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

//calculates circles position for the next frame
void step(SDL_Surface* surface, Circle* circle, Player* players[]){
	//check if players are in bounds 
	in_bounds(players);

	//if ball exits on the right side of the screen
	if (circle->x > WIDTH) {
		reset_circle(circle);
		reset_players(players[0], players[1]);
		players[0]->score++;
		SDL_Delay(1000);

	//if the ball exits on the left side of the screen
	} else if (circle->x < 0) {
		reset_circle(circle);
		reset_players(players[0], players[1]);
		players[1]->score++;
		SDL_Delay(1000);
	}
	//check if ball collides with one of the players
	for (int i=0; i<2; i++){
		//if they do, reverse the x velocity of the ball
		if (check_collision(circle, players[i])) {
			circle->v_x = -circle->v_x;
		}
	}
	//if circle hits off of the ceiling or the ground
	if (circle->y <= 0 || circle->y >= HEIGHT - circle->r) {
		//if it does, reverse the y velocity of the ball
		circle->v_y = -circle->v_y;
	}
	//increase the balls x and y by their velocity respectively
	circle->x += circle->v_x;
	circle->y += circle->v_y;
}

//resets player positions
void reset_players(Player* p1, Player* p2) {
	p1->x = PLAYER_1_X_INIT;
	p1->y = PLAYER_1_Y_INIT;
	p2->x = PLAYER_2_X_INIT;
	p2->y = PLAYER_2_Y_INIT;	
	
	//printf("PLAYER 1: %d\nPLAYER 2: %d\n\n", p1->score, p2->score);
}

//resets ball position and generates random x and y velocities for the ball
void reset_circle(Circle* circle) {
	circle->x = WIDTH/2;
	circle->y = HEIGHT/2;
	// rand()%2 generates a random num between 0 and 1
	// randomly assigns the balls' v_x and v_y
	circle->v_x = (rand()%2==0 ? BALL_SPEED: -BALL_SPEED);
	circle->v_y = (rand()%2==0 ? BALL_SPEED/2 : -BALL_SPEED/3);
}

// will return TRUE(1) if ball collides with player
int check_collision(Circle* circle, Player* player) {
	return (circle->x+circle->r > player->x &&
		circle->x-circle->r < player->x+player->w &&
		circle->y+circle->r > player->y &&
		circle->y-circle->r < player->y+player->h);
}

//makes sure players stay within the bounds of the screen
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

//handle user inputs
void input_handle(Player* player1, Player* player2, SDL_Window* window, int* programRunning) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W]) player1->y -= SPEED;
	if (keystate[SDL_SCANCODE_S]) player1->y += SPEED;
	if (keystate[SDL_SCANCODE_UP]) player2->y -= SPEED;
	if (keystate[SDL_SCANCODE_DOWN]) player2->y += SPEED;		
	if (keystate[SDL_SCANCODE_Q]) *programRunning = 0;
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
void render(SDL_Surface* surface, SDL_Window* window, Player* player1, Player* player2, Circle* circle, TTF_Font* font) {
	clear_screen(surface);
	draw_player(surface, player1);
	draw_player(surface, player2);
	draw_circle(surface,*circle);
	draw_score(surface, font, *player1, *player2);
	SDL_UpdateWindowSurface(window);
	//printf("RENDER!\n");
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

int main() {
	SDL_Window* window = init_window();
	SDL_Surface* surface = get_surface(window);
	TTF_Font* font = load_font();
	
	Player player1, player2;
	init_players(&player1, &player2);
	
	Circle circle;
	init_circle(&circle);	
	reset_circle(&circle);
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
		step(surface, &circle, players);
		in_bounds(players);
		render(surface, window, &player1, &player2, &circle, font);
		SDL_Delay(16); //approx 60 fps
	}
	shutdown(window);	
}

