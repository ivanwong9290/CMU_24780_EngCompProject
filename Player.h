#pragma once
#include <vector>

using namespace std;

class Player {

private:
	vector<vector<int>> hands;
	vector<int> hand;
	int bankBalance;
	int bet;
	bool canDouble;
	bool canSplit;
	bool canHit;
	
	//string playerName;    uncomment this to assign players name

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
	void doubleBet() { bet = 2 * bet; }
	int getHandSize() { return hand.size(); }
	int getCardValue(int i) { return hand[i]; }
	void setCardValue(int i, int newCardValue) { hand[i] = newCardValue; }
	bool checkSplit();
	bool checkDouble();
	void doubledown();
	void Split();
	void deleteCard() { hand.pop_back(); }
	void setCanDouble(bool input) { canDouble = input; }
	bool getDouble() { return canDouble; }
	void setCanSplit(bool input) { canSplit = input; }
	bool getSplit() { return canSplit; }
	void setCanHit(bool input) { canHit = input; }
	bool getHit() { return canHit; }
};