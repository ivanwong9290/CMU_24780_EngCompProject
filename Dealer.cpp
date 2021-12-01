#include <iostream>

#include "Dealer.h"



using namespace std;

void Dealer::setLevel()
{
	//ask user for dealer difficulty
	cout << "\n";
	cout << "Level of Difficulty: Beginner (1), Expert (2). ";
	cin >> level;
	cout << "\n";

	//If input is not a 1..
	if (level != 1)
	{
		//...or a 2.
		if (level != 2)
		{ 
			cin.clear();

			//Display error message and restart function. 
			cout << "Please enter your level of difficulty using the number 1 or 2." << endl;
			setLevel();
		}
	}
}

int Dealer::CheckHand()
{
	int sum = 0;
	int runningSum = 0;
	int handsize = hand.size();

	for (int i = 0; i < handsize; i++) {
		runningSum = hand[i];
		sum += runningSum;
	}
	
	return sum;
}

int Dealer::CheckHandAce()
{	int aceSum = 0;
	int aceRunSum = 0;
	int handsize = hand.size();
	bool foundAce = false;

	for (int i = 0; i < handsize; i++) {
		if (hand[i] == 11) {
			aceRunSum = 1;
			aceSum += aceRunSum;
		}
		else {
			aceRunSum = hand[i];
			aceSum += aceRunSum;

		}
	}
	return aceRunSum;
}

void Dealer::displayCards(bool hideCard)
{
	
	int handSize = hand.size();
	cout << "\n*****************";
	if (hideCard) {
		cout << "\nDealers Cards: ";
		cout << "** ";
		cout << hand[1];
		cout << "\n";
	}
	else {
		cout << "\nDealers Cards: ";
		for (int i = 0; i < handSize; i++) {
			
			cout << hand[i]<<" ";
		}
	}
}

bool Dealer::checkAce()
{
	int handsize = hand.size();

	for (int i = 0; i < handsize; i++) {
		if (hand[i] == 11)
			return true;
		
	}
	return false;
}


