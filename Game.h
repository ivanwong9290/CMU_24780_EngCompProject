#pragma once
#include <vector>

#include "Dealer.h"
#include "Player.h"
#include "Card.h"

using namespace std;


class Game {
private:
	vector<int>deck;
	Dealer theDealer;
	Player thePlayer;
	Deck theDeck;
	int wins;
	int totHands;
	bool play = true;
	bool draw;
	bool splitty = false;
	bool splitOcurred;
	bool duble;
	bool initialblackjack;
	bool playerBust;
	bool player2ndBust;
	bool dealerBust;
	bool playerHasBlackjack;
public:
	void displayRules();
	void playHand();
	void playAnotherHand();
	void playerWantsHit();
	void whoWins();
	void whoWins2nd();
	void hitUntilStand();
	void checkBust();
	void checkBust2nd();
	void blackJack();
	void immediateWin();
	void addWins() { wins++; }
	void addHands() { totHands++; }
	void displayStats();
	void betAmount();
	void decideSoftorHard();
	void decideSoftorHard2nd();
	void intelligentHand();
};
