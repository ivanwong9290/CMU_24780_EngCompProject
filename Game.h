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
	bool splitty;
	bool duble;
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
	void decideSoftorHard();
	void intelligentHand();
};