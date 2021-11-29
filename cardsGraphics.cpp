#include "cardsGraphics.h"

using namespace std;

// some setting issue here, so change the display method to texture display (similar with printCards)
void printBackground(YsRawPngDecoder png)
{
	//YsRawPngDecoder png;
	//png.Decode("table.png"); // Decode the texture
	GLuint texId;			// texture identifiers
	int imageWid = png.wid;
	int imageHei = png.hei;

	//png.Flip();		// uncomment this line and the switch case if your result on screen is flipped
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,       // the "A" in RGBA will include the transparency
		png.wid,    // the hippos width and height
		png.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png.rgba);

	// in order for textures to show, you must create a projection
	glViewport(0, 0, imageWid, imageHei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)imageWid - 1, (float)imageHei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);   // imageSample (a bird)

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	// scale the table
	/*double minX = wid * 0.25;
	double maxX = wid * 0.75;
	double minY = hei * 0.33;
	double maxY = hei * 0.66;*/

	glTexCoord2d(0, 0);   // these are "percentage" of the image
	glVertex2d(0, 0);        // these are actual pixel coordinates on screen

	glTexCoord2d(1, 0);
	glVertex2d(imageWid, 0);

	glTexCoord2d(1, 1);
	glVertex2d(png.wid, png.hei);

	glTexCoord2d(0, 1);
	glVertex2d(0, imageHei);

	// turn off blending
	glDisable(GL_BLEND);
	// turn off texture 
	glDisable(GL_TEXTURE_2D);
	glEnd();

	FsSwapBuffers();
	FsSleep(5);
}

// Drawing one specific cards to the screen, the coordinates are the bottom left corner of the cards
// Input:	suits: 'D': 1: DIAMOND, 'C': 2: CLUB, 'H'3: HEART  'S'4: SPADE, 
//			number 1-13: 1:ACE 11: JACK, 12: QUEEN, 13: KING, 15: THE BACK OF THE CARD
//			locX, locY, actual pixel coordinates on screen
//			wei, hei: size of the window
// notice: the card sequence in the texture is 2-10, J, Q, K and the last one is ACE, index 14 is JOKERS and back of the cards
//			first row is DIAMOND, second row is CLUB, third row is HEART, forth row is SPADE
// NOTE!!!: this function is for origin which locates at lower left corner, if the card on screen is fliped and with wrong suits, your origin is not set to bottom left
//			easy way to solve this is uncommont png.flip() and the other switch case
void printCards(char suitsChar, int index, double locX, double locY, double scale, double wid, double hei)
{
	YsRawPngDecoder png;
	png.Decode("cards.png"); // Decode the texture
	GLuint texId;			// texture identifiers
	int imageWid = png.wid;
	int imageHei = png.hei;
	
	//png.Flip();		// uncomment this line and the switch case if your result on screen is flipped
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,       // the "A" in RGBA will include the transparency
		png.wid,    // the hippos width and height
		png.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png.rgba);

	// in order for textures to show, you must create a projection
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

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);   // imageSample (a bird)

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// note: this funciton only works after you open a window -- FsOpenWindow is needed
	// preparetion ends, main drawing function starts

	// convert suitChar to integer
	// suits: 'C': 1: CLUB, 'D': 2: DIAMOND, 'H'3: HEART  'S'4: SPADE
	int suits = 0;
	switch (suitsChar) {
	case 'D':
		suits = 1;
		break;
	case 'C':
		suits = 2;
		break;
	case 'H':
		suits = 3;
		break;
	case 'S':
		suits = 4;
		break;
	default:
		suits = -1;
	}

	// switch case prepared for flipped case
	/*switch (suitsChar) {
	case 'C':
		suits = 1;
		break;
	case 'D':
		suits = 2;
		break;
	case 'H':
		suits = 1;
		break;
	case 'S':
		suits = 2;
		break;
	default:
		suits = -1;
	}*/


	if (index == 1)
		index = 14; // ACE locates at the end of the row

	if (index <= 15 && suits != -1) {
		double drawWidth = (imageWid / 14.0) * scale;
		double drawHeight =(imageHei / 4.0) * scale;
		double minX = (index - 2.0) / 14.0;
		double maxX = (index - 1.0) / 14.0;
		double minY = (suits - 1.0) / 4.0;
		double maxY = (suits) / 4.0;

		// think of rectangle as vertices A, B, C, D (defined counter-clockwise)
		// A is at lower left, B is at lower right, C is at upper right, D is at upper left

		/*double Ax = locX, Ay = locY;
		double Bx = Ax + drawWidth * cosTheta, By = Ay - drawWidth * sinTheta;
		double Cx = Bx - drawHeight * sinTheta, Cy = By - drawHeight * cosTheta;
		double Dx = Ax - drawHeight * sinTheta, Dy = Ay - drawHeight * cosTheta;*/


		double Ax = locX, Ay = locY;
		double Bx = Ax + drawWidth, By = Ay;
		double Cx = Bx, Cy = By + drawHeight;
		double Dx = Ax, Dy = Ay + drawHeight;

		glBegin(GL_QUADS);
		glTexCoord2d(minX, maxY);   // these are "percentage" of the image
		glVertex2d(Ax, Ay);        // these are actual pixel coordinates on screen

		glTexCoord2d(maxX, maxY);
		glVertex2d(Bx, By);

		glTexCoord2d(maxX, minY);
		glVertex2d(Cx, Cy);

		glTexCoord2d(minX, minY);
		glVertex2d(Dx, Dy);

		// turn off blending
		glDisable(GL_BLEND);
		// turn off texture 
		glDisable(GL_TEXTURE_2D);
		glEnd();

	}
	else {
		cout << "Don't have information for this card: " << suits << index << endl;
	}
}

void displayMenu() {
	int mouseEvent, leftButton, middleButton, rightButton;
	int screenX, screenY;
	Point2D modelCoord;
	stringstream coordStream; // for displaying coordinates on screen

	bool terminate = false;

	while (!false) {
		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, screenX, screenY);

		//if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
		//	// make gear under mouse the current gear
		//	modelCoord = getModelCoords(screenX, screenY,
		//		originX, originY, scale);
		//	int i = 0;
		//	while (i < allGears.size()
		//		&& !(allGears[i].pointIsInGear(modelCoord)))
		//		i++;

		//	if (i < allGears.size()) // found a gear under mouse
		//		currGearIndex = i;
		//}
		//if (leftButton) {
		//	// write coords on screen if left button is held down
		//	modelCoord = getModelCoords(screenX, screenY,
		//		originX, originY, scale);
		//	coordStream.str("");  // reset stream
		//	coordStream.precision(4);
		//	coordStream << modelCoord.x << ", " << modelCoord.y;
		//	glColor3ub(60, 230, 60);
		//	glRasterPos2i(screenX, screenY);  // set position
		//	YsGlDrawFontBitmap7x10(coordStream.str().c_str());
		//}
	}
}



Point2D getModelCoords(int screenX, int screenY, float originX, float originY, float scale) {
	int wei, hei;
	FsGetWindowSize(wei, hei);
	return { screenX / scale + originX, (hei - screenY) / scale + originY };
}


// Drawing one specific cards to the screen, the coordinates are the bottom left corner of the cards
// Input:	suits: 'D': 1: DIAMOND, 'C': 2: CLUB, 'H'3: HEART  'S'4: SPADE, 
//			number 1-13: 1:ACE 11: JACK, 12: QUEEN, 13: KING, 15: THE BACK OF THE CARD
//			locX, locY, actual pixel coordinates on screen
//			wei, hei: size of the window
// notice: the card sequence in the texture is 2-10, J, Q, K and the last one is ACE, index 14 is JOKERS and back of the cards
//			first row is DIAMOND, second row is CLUB, third row is HEART, forth row is SPADE
// NOTE!!!: this function is for origin which locates at lower left corner, if the card on screen is fliped and with wrong suits, your origin is not set to bottom left
//			easy way to solve this is uncommont png.flip() and the other switch case
void printCards(vector<Card*> decks, double locX, double locY, double scale, double wid, double hei)
{

	YsRawPngDecoder png;
	png.Decode("cards.png"); // Decode the texture
	GLuint texId;			// texture identifiers
	int imageWid = png.wid;
	int imageHei = png.hei;

	//png.Flip();		// uncomment this line and the switch case if your result on screen is flipped
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,       // the "A" in RGBA will include the transparency
		png.wid,    // the hippos width and height
		png.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		png.rgba);

	// in order for textures to show, you must create a projection
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

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);   // imageSample (a bird)

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// note: this funciton only works after you open a window -- FsOpenWindow is needed
	// preparetion ends, main drawing function starts

	// convert suitChar to integer
	// suits: 'C': 1: CLUB, 'D': 2: DIAMOND, 'H'3: HEART  'S'4: SPADE

	// calculate the shift of each cards
	double shift = 0.;

	// for loop is used for card decks
	for (int i = 0; i < decks.size(); i++) {
		int index = decks[i]->getCardNumber();
		int suits = decks[i]->getCardSuit();


		/*int suits = 0;
		switch (suitsChar) {
		case 'D':
			suits = 1;
			break;
		case 'C':
			suits = 2;
			break;
		case 'H':
			suits = 3;
			break;
		case 'S':
			suits = 4;
			break;
		default:
			suits = -1;
		}*/

		// switch case prepared for flipped case
		/*switch (suitsChar) {
		case 'C':
			suits = 1;
			break;
		case 'D':
			suits = 2;
			break;
		case 'H':
			suits = 1;
			break;
		case 'S':
			suits = 2;
			break;
		default:
			suits = -1;
		}*/


		if (index == 1)
			index = 14; // ACE locates at the end of the row

		if (index <= 15 && suits != -1) {
			double drawWidth = (imageWid / 14.0) * scale;
			double drawHeight = (imageHei / 4.0) * scale;
			double minX = (index - 2.0) / 14.0;
			double maxX = (index - 1.0) / 14.0 - (5.0 / 4800.);
			double minY = (suits - 1.0) / 4.0;
			double maxY = (suits) / 4.0;

			// think of rectangle as vertices A, B, C, D (defined counter-clockwise)
			// A is at lower left, B is at lower right, C is at upper right, D is at upper left

			/*double Ax = locX, Ay = locY;
			double Bx = Ax + drawWidth * cosTheta, By = Ay - drawWidth * sinTheta;
			double Cx = Bx - drawHeight * sinTheta, Cy = By - drawHeight * cosTheta;
			double Dx = Ax - drawHeight * sinTheta, Dy = Ay - drawHeight * cosTheta;*/


			//double Ax = locX + shift, Ay = locY;
			//double Bx = Ax + drawWidth, By = Ay;
			//double Cx = Bx, Cy = By + drawHeight;
			//double Dx = Ax, Dy = Ay + drawHeight;

			//glBegin(GL_QUADS);
			//glTexCoord2d(minX, maxY);   // these are "percentage" of the image
			//glVertex2d(Ax, Ay);        // these are actual pixel coordinates on screen

			//glTexCoord2d(maxX, maxY);
			//glVertex2d(Bx, By);

			//glTexCoord2d(maxX, minY);
			//glVertex2d(Cx, Cy);

			//glTexCoord2d(minX, minY);
			//glVertex2d(Dx, Dy);

			double Ax = locX + shift, Ay = locY;
			double Bx = Ax + drawWidth, By = Ay;
			double Cx = Bx, Cy = By + drawHeight;
			double Dx = Ax, Dy = Ay + drawHeight;

			glBegin(GL_QUADS);
			glTexCoord2d(minX, minY);   // these are "percentage" of the image
			glVertex2d(Ax, Ay);        // these are actual pixel coordinates on screen

			glTexCoord2d(maxX, minY);
			glVertex2d(Bx, By);

			glTexCoord2d(maxX, maxY);
			glVertex2d(Cx, Cy);

			glTexCoord2d(minX, maxY);
			glVertex2d(Dx, Dy);

			// turn off blending
			glDisable(GL_BLEND);
			// turn off texture 
			glDisable(GL_TEXTURE_2D);
			glEnd();

			// shift the coordinates
			shift += 0.15 * (imageWid / 14.0) * scale;
		}
		else {
			cout << "Don't have information for this card: " << suits << index << endl;
		}
	}
}


//int main(void) {
//	// Test print background
//	//void printBackground();
//	//YsRawPngDecoder png;
//	//if (YSOK == png.Decode("table.png")) {
//	//	//printf("Read Width=%d Height=%d\n", png.wid, png.hei);
//	//	cout << "Read Width=" << png.wid << " Height=" << png.hei << endl;
//	//	png.Flip();
//	//}
//	//else {
//	//	printf("Read Error!\n");
//	//	cout << "Read Error!" << endl;
//	//	return 0;
//	//}
//
//	//FsOpenWindow(16, 16, png.wid, png.hei, 1);
//	//int key = FSKEY_NULL;
//	//while (FSKEY_ESC != key) {
//	//	FsPollDevice();
//	//	key = FsInkey();
//	//	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//
//	//	int winWid, winHei;
//	//	FsGetWindowSize(winWid, winHei);
//	//	glRasterPos2d(0.0, (double)(winHei - 1));
//	//	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
//
//	//	FsSwapBuffers();
//	//	FsSleep(50);
//	//}
//
//	// Test draw cards, the card should be 5 of club, flipped
//	FsOpenWindow(16, 16, 800, 600, 1);
//
//	int key = FSKEY_NULL;
//	while (FSKEY_ESC != key) {
//		FsPollDevice();
//
//		key = FsInkey();
//
//		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//
//		printBackground();
//
//		// draw the letters
//		/*drawCards('C', 5, 100, 200, 1, 800, 600);
//		drawCards('S', 1, 600, 200, 0.5, 800, 600);*/
//		printCards('H', 15, 350, 400, 0.3);
//
//
//		FsSwapBuffers();
//	}
//
//	return 0;
//}


//int main(void) {
//	vector<Card*> testDeck;
//	Card* card1 = new Card(2, 4);
//	testDeck.push_back(card1);
//
//	Card* card2 = new Card(1, 2);
//	testDeck.push_back(card2);
//	Card* card3 = new Card(13, 2);
//	testDeck.push_back(card3);
//	Card* card4 = new Card(11, 1);
//	testDeck.push_back(card4);
//
//	// Test draw cards, the card should be 5 of club, flipped
//	FsOpenWindow(16, 16, 800, 600, 1);
//
//	int key = FSKEY_NULL;
//	while (FSKEY_ESC != key) {
//		FsPollDevice();
//
//		key = FsInkey();
//
//		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//
//		printBackground();
//
//		// draw the letters
//		/*drawCards('C', 5, 100, 200, 1, 800, 600);
//		drawCards('S', 1, 600, 200, 0.5, 800, 600);*/
//		//printCards('H', 15, 350, 400, 0.3);
//
//		printCards(testDeck, 200, 0, 0.3);
//		FsSwapBuffers();
//	}
//}