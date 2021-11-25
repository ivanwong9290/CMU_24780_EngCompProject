#pragma once
#include <vector>

using namespace std;

class Player {

private:
	vector<vector<int>> hands;
	vector<int> hand;
	vector<int> secondHand;
	double bankBalance;
	double bet;
	bool canDouble;
	bool canSplit;
	bool canHit;
	
	//string playerName;    uncomment this to assign players name

public:
	int CheckHand();
	int Check2ndHand();
	void Hit(int newCard) { hand.push_back(newCard); }
	void Hit2nd(int newCard) { secondHand.push_back(newCard); }
	void displayCards();
	void display2nd();
	void eraseHand() { hand.clear(); secondHand.clear(); }
	void getHandValue();
	void get2ndValue();
	int getBankBalance() { return bankBalance; }
	int getBet() { return bet; }
	void setBankBalance(int GameBalance) { bankBalance = GameBalance; }
	void subBankBalance(int betLoss) { bankBalance = bankBalance - betLoss; }
	void addBankBalance(int betWin) { bankBalance = bankBalance + betWin; }
	void setBet(int handBet) { bet = handBet; }
	void doubleBet() { bet = 2 * bet; }
	int getHandSize() { return hand.size(); }
	int get2ndSize() { return secondHand.size(); }
	int getCardValue(int i) { return hand[i]; }
	int get2ndValue(int i) { return secondHand[i]; }
	void setCardValue(int i, int newCardValue) { hand[i] = newCardValue; }
	void set2ndValue(int i, int newCardValue){ secondHand[i] = newCardValue; }
	bool checkSplit();
	bool checkDouble();
	void doubledown();
	void Split(int cardThree, int cardFour);
	void deleteCard() { hand.pop_back(); }
	void setCanDouble(bool input) { canDouble = input; }
	bool getDouble() { return canDouble; }
	void setCanSplit(bool input) { canSplit = input; }
	bool getSplit() { return canSplit; }
	void setCanHit(bool input) { canHit = input; }
	bool getHit() { return canHit; }
};