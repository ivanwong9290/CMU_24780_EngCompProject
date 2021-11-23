#pragma once
#include <vector>

using namespace std;

class Dealer {
	
private:
	vector<int> hand;
	int level;

public:
	
	void setLevel();	
	int CheckHand();
	void Hit(int newCard) { hand.push_back(newCard); }
	void displayCards(bool hideCard);
	int getHandSize() { return hand.size(); }
	int getCardValue(int i) { return hand[i]; }
	void setCardValue(int i, int newCardValue) { hand[i] = newCardValue; }
	void eraseHand() { hand.clear(); }
	int CheckHandAce();
	bool checkAce();
};