#include "player.h"


//initialize players
void init_players(Player* player1, Player* player2) {
	*player1 = (Player) {
		PLAYER_1_X_INIT,
		PLAYER_1_Y_INIT,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		0,
    COLOR_WHITE
	};
	
	*player2 = (Player) {
		PLAYER_2_X_INIT,
		PLAYER_2_Y_INIT,
		PLAYER_WIDTH,
		PLAYER_HEIGHT,
		0,
    COLOR_WHITE
	};

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




