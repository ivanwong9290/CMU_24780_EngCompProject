#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <ctype.h>
//#include <math.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "GraphicFont.h"


class gameplay {
public:
	gameplay();
	~gameplay();

	void start_game();
	void end_game();

	int getplayerscore();
	int getdealerscore();

};


