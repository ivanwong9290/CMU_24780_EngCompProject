#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <ctype.h>

#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "GraphicFont.h"
#include "display.h"
#include "Game.h"


void display::intro() {

	YsRawPngDecoder png;
	png.Decode("blackjack_welcome2.png"); //decode welcome image

	GLuint texId;


	auto start = std::chrono::system_clock::now();
	std::chrono::duration<double> dur;
	dur = std::chrono::system_clock::now() - start;

	//load welcome image
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// Create a projection for texture 
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);


	//Make Welcome image fade in************************************
	for (float alpha = 1.0; alpha > 0.0; alpha -= 0.01) {
		glEnable(GL_BLEND); //Enable blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0 - alpha, 1.0 - alpha, 1.0 - alpha, 1.0);

		//show image
		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();
		glDisable(GL_BLEND);// turn off blending
		FsSwapBuffers();
		FsSleep(5);
	}

	FsPollDevice();

	while (dur.count() < 6.0) {
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//FsPollDevice();

		//DISPLAY IMAGE****************************************
		glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

		// set up parameters for the current texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

		int wid, hei;
		FsGetWindowSize(wid, hei);

		// Create a projection for texture 
		glViewport(0, 0, wid, hei);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

		// enable texture mapping
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();

		FsSwapBuffers();
		FsSleep(5);
		FsPollDevice();
		dur = std::chrono::system_clock::now() - start;

	}
	

	//MAKE IMAGE FADE OUT**************************
	for (float alpha = 0.05; alpha < 1.0; alpha += 0.01) {
		glEnable(GL_BLEND); //Enable blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0, 0.0, 0.0, alpha);
		//glColor4f(alpha, alpha, alpha, alpha);
		glBegin(GL_QUADS);
		glVertex2f(0.0, 0.0);
		glVertex2f(1280.0, 0.0);
		glVertex2f(1280.0, 720.0);
		glVertex2f(0.0, 720.0);

		glEnd();
		glDisable(GL_BLEND);// turn off blending
		FsSwapBuffers();
		FsSleep(5);
	}
}



std::string display::enter_name()
{
	YsRawPngDecoder png;
	png.Decode("green_background.png"); //decode image
	
	GLuint texId;

	//load image
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// Create a projection for texture 
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);
		
		
	int key = FsInkey();
	std::string playerName = "";

	FsPollDevice();

	while (key != FSKEY_ENTER) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();



		//display enter name message
		glColor3f(100000, 100000, 100000);
		glRasterPos2d(160, 225);
		YsGlDrawFontBitmap20x32("Please enter your name. Press ENTER when done...");


		//build playerName from keyboard entry 
		DrawingUtilNG::buildStringFromFsInkey(key, playerName);

		playerName += "_"; // add an underscore as prompt
		glRasterPos2i(165, 275);  // sets position
		YsGlDrawFontBitmap20x32(playerName.c_str());
		playerName = playerName.substr(0, playerName.length() - 1); // remove underscore
		glColor3f(1.0f, 1.0f, 1.0f);


		FsSwapBuffers();
		FsSleep(25);
		FsPollDevice();
		key = FsInkey();
	}

	if (key == FSKEY_ENTER) {
		//glColor3f(1, 0, 0);
		//glRasterPos2d(140, 400);
		//YsGlDrawFontBitmap20x32("Loading . . .");

		FsSwapBuffers(); // this keeps the other stuff on because the previous buffer had it too
		return playerName;
	}
	else {
		return "";
	}
	
}


std::string display::set_playerName(std::string name)
{
	playerName = name;
	return playerName;
}


std::string display::get_playerName()
{
	return playerName;
}


void display::welcome_to_game()
{
	YsRawPngDecoder png;
	png.Decode("green_background.png"); //decode image

	auto start = std::chrono::system_clock::now();
	std::chrono::duration<double> dur;
	dur = std::chrono::system_clock::now() - start;

	GLuint texId;

	//load image
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// Create a projection for texture 
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	FsPollDevice();

	while (dur.count() < 3.0) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();
		
		
		
		//display enter name message
		glColor3f(100000, 100000, 100000);
		glRasterPos2d(360, 225);
		YsGlDrawFontBitmap20x32("Welcome to Blackjack...");
		
		glColor3f(100000, 100000, 100000);
		glRasterPos2d(850, 225);
		YsGlDrawFontBitmap20x32(get_playerName().c_str());
		glColor3f(1.0f, 1.0f, 1.0f);

		FsSwapBuffers();
		FsSleep(25);
		FsPollDevice();

		dur = std::chrono::system_clock::now() - start;
	}
}

//int display::main_menu(YsRawPngDecoder png)
int display::main_menu()
{
	YsRawPngDecoder png;
	png.Decode("main_menu.png"); //decode main menu image

	GLuint texId;

	//load image
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// Create a projection for texture 
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);


	bool state_determine = false;
	int game_state;

	while (state_determine == false) {
		
		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();


		//MOUSE EVENTS

		int mouseEvent, leftButton, middleButton, rightButton;
		int locX, locY;

		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, locX, locY);

		if (locX >= 497 && locX <= 808) {
			if (locY >= 266 && locY <= 352) {  //mouse on start button
				//draw rectangle around button
				glLoadIdentity();
				
				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 261);
				glVertex2f(499, 261);
				glVertex2f(499, 357);
				glVertex2f(492, 357);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 261);
				glVertex2f(492, 268);
				glVertex2f(813, 268);
				glVertex2f(813, 261);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(806, 261);
				glVertex2f(813, 261);
				glVertex2f(813, 357);
				glVertex2f(806, 357);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 350);
				glVertex2f(813, 350);
				glVertex2f(813, 357);
				glVertex2f(492, 357);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
					game_state = 1;
					state_determine = true;
				}
			}
			else if (locY >= 381 && locY <= 467) {  //mouse on rules button
				//draw rectangle around button
				glLoadIdentity();

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 376);
				glVertex2f(499, 376);
				glVertex2f(499, 472);
				glVertex2f(492, 472);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 376);
				glVertex2f(813, 376);
				glVertex2f(813, 383);
				glVertex2f(492, 383);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(806, 376);
				glVertex2f(813, 376);
				glVertex2f(813, 472);
				glVertex2f(806, 472);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 465);
				glVertex2f(813, 465);
				glVertex2f(813, 472);
				glVertex2f(492, 472);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);


				if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
					game_state = 2;
					state_determine = true;
				}
			}
			else if (locY >= 496 && locY <= 582) {  //mouse on quit button
				//draw rectangle around button
				glLoadIdentity();

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 491);
				glVertex2f(499, 491);
				glVertex2f(499, 587);
				glVertex2f(492, 587);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 491);
				glVertex2f(813, 491);
				glVertex2f(813, 498);
				glVertex2f(492, 498);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(806, 491);
				glVertex2f(813, 491);
				glVertex2f(813, 587);
				glVertex2f(806, 587);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);

				glBegin(GL_POLYGON);
				glColor3ub(255, 255, 255);
				glVertex2f(492, 580);
				glVertex2f(813, 580);
				glVertex2f(813, 587);
				glVertex2f(492, 587);
				glEnd();
				glColor3f(1.0f, 1.0f, 1.0f);


				if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
					game_state = 0;
					state_determine = true;
				}
			}
		}

		FsSwapBuffers();
		FsSleep(5);
		FsPollDevice();
	}

	return game_state;

}

int display::play_game() {
	
	YsRawPngDecoder png;
	png.Decode("table.png"); //decode table image
	
	GLuint texId;

	//load image
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// Create a projection for texture 
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	int state = 1; //game is on

	while (state == 1) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();

		

		FsSwapBuffers();
		FsSleep(5);
		//FsPollDevice();

		Game theGame;
		state = theGame.playHand(); //state = 0 when game ends

	}
	return state;
	
}


void display::rules()
{
	YsRawPngDecoder png;
	png.Decode("Rules.png");
	GLuint texId;

	//load image
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

	int wid, hei;
	FsGetWindowSize(wid, hei);

	// Create a projection for texture 
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	bool main_menu = false;

	while (main_menu == false) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		double scale1 = 1.0;
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		// For each vertex, assign texture coordinate before vertex coordinate.
		glTexCoord2d(0.0, 0.0); //image upper left   
		glVertex2i(0, 0); // //screen rectangle upper left

		glTexCoord2d(1.0, 0.0); //image upper right
		glVertex2i(xSize, 0); //screen rectange upper right

		glTexCoord2d(1.0, 1.0); //image lower right
		glVertex2i(xSize, ySize); //screen rectangle lower right

		glTexCoord2d(0.0, 1.0); //image bottom left
		glVertex2i(0, ySize); //screen rectangle lower left

		glEnd();


		int mouseEvent, leftButton, middleButton, rightButton;
		int locX, locY;

		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, locX, locY);

		if (locX >= 22 && locX <= 278 && locY >= 22 && locY <= 87) {
			//draw rectangle around button
			glLoadIdentity();

			glBegin(GL_POLYGON);
			glColor3ub(255, 255, 255);
			glVertex2f(17, 17);
			glVertex2f(17, 92);
			glVertex2f(24, 92);
			glVertex2f(24, 17);
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_POLYGON);
			glColor3ub(255, 255, 255);
			glVertex2f(17, 17);
			glVertex2f(283, 17);
			glVertex2f(283, 24);
			glVertex2f(17, 24);
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_POLYGON);
			glColor3ub(255, 255, 255);
			glVertex2f(283, 17);
			glVertex2f(283, 92);
			glVertex2f(276, 92);
			glVertex2f(276, 17);
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_POLYGON);
			glColor3ub(255, 255, 255);
			glVertex2f(17, 85);
			glVertex2f(283, 85);
			glVertex2f(283, 92);
			glVertex2f(17, 92);
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);

			if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
				main_menu = true;
			}
		}
		FsSwapBuffers();
		FsSleep(5);
		FsPollDevice();
	}
	return;
}
