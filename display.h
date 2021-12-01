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

	void intro();
	std::string enter_name();

	std::string set_playerName(std::string name);
	std::string get_playerName();

	void welcome_to_game();

	int main_menu();

	int play_game();
	void rules();

};