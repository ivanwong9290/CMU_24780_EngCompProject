#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

#include "yspng.h"

class display {

private:
	std::string playerName;

public:

	void intro(YsRawPngDecoder png);
	std::string enter_name(YsRawPngDecoder png);

	std::string set_playerName(std::string name);
	std::string get_playerName();

	void welcome_to_game(YsRawPngDecoder png);

	int main_menu(YsRawPngDecoder png);

	void play_game(YsRawPngDecoder png);
	//void rules();
	//void quit_game();


};