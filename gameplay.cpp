#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <ctype.h>
#include "DrawingUtilNG.h"
//#include <math.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "GraphicFont.h"
#include "gameplay.h"

using namespace std;

//constructor
gameplay::gameplay() {

	//opengl display is open
	string inFileName;
	ifstream inFile;
	inFileName = "Enter file name of model to load.";
	string fileName = "";

	int key;
	FsPollDevice();
	key = FsInkey();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


	// show list of available files (need C++17 to work, set in project props)
	glRasterPos2d(440, 330);
	YsGlDrawFontBitmap12x16("Please enter your name:");


	// build filename from keyboard entry, letter by letter
	DrawingUtilNG::buildStringFromFsInkey(key, fileName);

	fileName += "_"; // add an underscore as prompt
	glRasterPos2i(165, 275);  // sets position
	YsGlDrawFontBitmap16x24(fileName.c_str());
	fileName = fileName.substr(0, fileName.length() - 1); // remove underscore

	FsSwapBuffers();
	FsSleep(25);

	FsPollDevice();
	key = FsInkey();

}

//destructor
gameplay::~gameplay(void) 
{
}