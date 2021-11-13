#pragma once
#include <vector>

using namespace std;

class Player {

private:
	vector<int> hand;
	int bankBalance;
	int bet;

public:
	int CheckHand();
	void Hit(int newCard) { hand.push_back(newCard); }
	void displayCards();
	void eraseHand() { hand.clear(); }
	void getHandValue();
	int getBankBalance() { return bankBalance; }
	int getBet() { return bet; }
	void setBankBalance(int GameBalance) { bankBalance = GameBalance; }
	void subBankBalance(int betLoss) { bankBalance = bankBalance - betLoss; }
	void addBankBalance(int betWin) { bankBalance = bankBalance + betWin; }
	void setBet(int handBet) { bet = handBet; }
	int getHandSize() { return hand.size(); }
	int getCardValue(int i) { return hand[i]; }
	void setCardValue(int i, int newCardValue) { hand[i] = newCardValue; }
};