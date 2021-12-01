#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "display.h"
#include "cardsGraphics.h"
#include "Game.h"

//using namespace std;

void clear(void) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	FsPollDevice();
}

int main(void) {

	display display_state; //load screen object
	YsSoundPlayer player1; //load game background sound
	YsSoundPlayer::SoundData myWav1;
	//int key; // for keyboard keys

	
	//Game flags for changing states
	bool game_on = true; //bool for if game is being played (true) or quit (false)


	//Open graphics window
	FsOpenWindow(16, 16, 1280, 720, 1, "Blackjack!");
	
	//start game audio
	myWav1.LoadWav("casino_background_jazz.wav");
	player1.Start();
	player1.PlayBackground(myWav1);

	while (game_on && YSTRUE == player1.IsPlaying(myWav1)) {
		
		clear();

		//display intro image (Blackjack screen)
		display_state.intro();

		clear();

		//display please enter player name
		display_state.set_playerName(display_state.enter_name());

		clear();

		//display welcome to blackjack player...
		display_state.welcome_to_game();

		int state = 3;

		while (state != 0) {
			clear();
			state = display_state.main_menu();
			clear();
			if (state == 1) {
				state = display_state.play_game();
			}
			else if (state == 2) {
				display_state.rules();
			}
			else if (state == 0) {
				game_on = false;
			}
		}
		game_on = false;

	}
			
	FsSleep(5);
			
	if (!game_on) {
		FsCloseWindow();
		return 0; //end game
	}
}
