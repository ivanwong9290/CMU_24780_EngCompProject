#pragma once
#include <vector>

#include "Dealer.h"
#include "Player.h"
#include "Card.h"

using namespace std;


class Game {
private:
	vector<Card*>PlayerDeck;
	vector<Card*>DealerDeck;
	Dealer theDealer;
	Player thePlayer;
	Deck theDeck;
	int dealerCardCount=-1;
	int playerCardCount=-1;
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
	bool betInsurance;
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
	void addDealerCardCount() { dealerCardCount++; }
	void addPlayerCardCount() { playerCardCount++; }
	int getDealerCardCount() { return dealerCardCount; }
	int getPlayerCardCount() { return playerCardCount; }
};
