#pragma once
#include <vector>

#include "Dealer.h"
#include "Player.h"

using namespace std;


class Game {
private:
	vector<int>deck;
	Dealer theDealer;
	Player thePlayer;
	int wins;
	int totHands;
	bool play = true;
	bool draw;
	bool initialblackjack;
	bool playerBust;
	bool dealerBust;
	bool playerHasBlackjack;
public:
	void displayRules();
	void playHand();
	void playAnotherHand();
	void playerWantsHit();
	void whoWins();
	void hitUntilStand();
	void checkBust();
	void blackJack();
	int getCard();
	void shuffla();
	void intializeDeck();
	void immediateWin();
	void addWins() { wins++; }
	void addHands() { totHands++; }
	void displayStats();
	void betAmount();
	void checkSoftOrHard();
};