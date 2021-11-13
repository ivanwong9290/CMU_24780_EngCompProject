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
	void eraseHand() { hand.clear(); }
};