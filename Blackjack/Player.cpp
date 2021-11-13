#include <iostream>

#include "Player.h"

using namespace std;



int Player::CheckHand()
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

void Player::displayCards()
{
	int handsize = hand.size();
	cout << "\n*****************";
	cout << "\nUsers Cards: ";
		for (int i=0; i < handsize; i++) {
			
			cout << hand[i]<<" ";
		}
}

void Player::getHandValue()
{
	int sum = 0;
	int runningSum = 0;
	int handsize = hand.size();

	for (int i = 0; i < handsize; i++) {
		runningSum = hand[i];
		sum += runningSum;
	}
	cout<< "\nUser hand value: "<< sum;
	
}
