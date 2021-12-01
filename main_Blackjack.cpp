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
	int key; // for keyboard keys

	//Decode images
	YsRawPngDecoder png[5];
	png[0].Decode("blackjack_welcome2.png"); //decode welcome image
	png[1].Decode("green_background.png"); //decode green background
	png[2].Decode("green_background.png"); //decode green background
	png[3].Decode("main_menu.png"); //decode main menu image
	png[4].Decode("table.png");

	//GLuint texId;

	
	//Game flags for changing states
	bool game_on = true; //bool for if game is being played (true) or quit (false)
	bool flag = false; //flag to determine if current game has ended

	//Clock just to measure time for fyi
	auto start = std::chrono::system_clock::now();
	std::chrono::duration<double> dur;
	dur = std::chrono::system_clock::now() - start;

	//Open graphics window
	FsOpenWindow(16, 16, 1280, 720, 1, "Blackjack!");
	
	//start game audio
	myWav1.LoadWav("casino_background_jazz.wav");
	player1.Start();
	player1.PlayBackground(myWav1);

	while (game_on && YSTRUE == player1.IsPlaying(myWav1)) {

		key = FsInkey();
		
		clear();

		//display intro image (Blackjack screen)
		display_state.intro(png[0]);

		clear();

		//display please enter player name
		display_state.set_playerName(display_state.enter_name(png[1]));

		clear();

		//display welcome to blackjack player...
		display_state.welcome_to_game(png[2]);

		clear();

		//display main menu
		int state = display_state.main_menu(png[3]);

		clear();

		if (state == 1) {
			//printBackground(png[4]);
			display_state.play_game(png[4]);
			
			
		}
		//else if (state == 2) {
		//	display_state.rules();
		//}
		//else if (state == 0) {
		//	display_state.quit_game();
		//}


		//keyboard interactions after welcome page
		switch (key) {
		case FSKEY_ESC:   // exit program
			game_on = false;
			break;
		}

	}
			
		FsSleep(5);
			
			//Show main menu (rules in one corner, start game, quit game

			// game ends (set flag to 1). Then ask user if they want to play again or quit
				//if key "A" is pressed or play again button is clicked
					//restart while loop, set flag to 0	
				//if key "Q" is pressed or quit button is clicked
					//game_on = false;
					//break;

	if (!game_on) {
		//display Thank you for playing
		FsCloseWindow();
		return 0; //end game
	}
}


