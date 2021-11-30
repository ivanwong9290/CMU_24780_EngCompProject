#pragma once
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctype.h>

#include "Card.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "DrawingUtilNG.h"


/*
* User interface of the team project: Black Jack, the main tasks are: tracking mouse, display cards, display background
*/

struct Point2D {
	float x, y;
};

// Draw the table to the openGL
void printBackground(double wid = 800, double hei = 600);

// Draw the card to specific location, try to follow the function drawText()
// void GraphicFont::drawText(const string& aString, double locX, double locY, double scale, double theta)
// {
//	 glColor4d(red, green, blue, alpha);
//	 // enable texture mapping
//	 glEnable(GL_TEXTURE_2D);
//
//   // bind a texture to OpenGL primitives
//	 glBindTexture(GL_TEXTURE_2D, textureID);
//
//	 // turn on blending so that transparency can be applied
//	 glEnable(GL_BLEND);
//	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	 // draw the letters
//	 for (int i = 0; i < aString.length(); i++) {
//		 drawLetter(aString[i], locX, locY, scale, theta);
//	 }
//
//	 // turn off blending 
//	 glDisable(GL_BLEND);
//	 // turn off texture 
//	 glDisable(GL_TEXTURE_2D);
//
//}
void printCards(char suitsChar, int index, double locX, double locY, double scale = 0.3, double wid = 800, double hei = 600);

// combined with cardsGraphics
void printCards(vector<Card*> decks, double locX, double locY, bool isDealer = false, double scale = 0.3, double wid = 800, double hei = 600);

// display a menu onto the console and track the mouse movement
void displayMenu();

Point2D getModelCoords(int screenX, int screenY, float originX, float originY, float scale);