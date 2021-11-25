#include <iostream>

#include "Player.h"
#include "Game.h"

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

int Player::Check2ndHand()
{
	int sum = 0;
	int runningSum = 0;
	int handsize = secondHand.size();

	for (int i = 0; i < handsize; i++) {
		runningSum = secondHand[i];
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

void Player::display2nd()
{
	int handsize = secondHand.size();
	cout << "\n*****************";
	cout << "\nUsers Cards: ";
	for (int i = 0; i < handsize; i++) {

		cout << secondHand[i] << " ";
	}
}

void Player::getHandValue()
{
	int sum = 0;
	int aceSum = 0;
	int runningSum = 0;
	int aceRunSum = 0;
	int handsize = hand.size();
	bool foundAce = false;

	for (int i = 0; i < handsize; i++) {
		if (hand[ i ] == 11) {
			runningSum = hand[i];
			aceRunSum = 1;
			sum += runningSum;
			aceSum += aceRunSum;
			foundAce = true;
		}
		else {
			runningSum = hand[i];
			aceRunSum = hand[i];
			sum += runningSum;
			aceSum += aceRunSum;

		}
	}
	if (foundAce == true && sum!=21) 
		cout<< "\nPotential user hand values are: " << sum << " or " << aceSum;
	else 
		cout<< "\nUser hand value: "<< sum;
	
}

void Player::get2ndValue()
{
	int sum = 0;
	int aceSum = 0;
	int runningSum = 0;
	int aceRunSum = 0;
	int handsize = secondHand.size();
	bool foundAce = false;

	for (int i = 0; i < handsize; i++) {
		if (secondHand[i] == 11) {
			runningSum = secondHand[i];
			aceRunSum = 1;
			sum += runningSum;
			aceSum += aceRunSum;
			foundAce = true;
		}
		else {
			runningSum = secondHand[i];
			aceRunSum = secondHand[i];
			sum += runningSum;
			aceSum += aceRunSum;

		}
	}
	if (foundAce == true && sum != 21)
		cout << "\nPotential user hand values are: " << sum << " or " << aceSum;
	else
		cout << "\nUser hand value: " << sum;

}

bool Player::checkSplit()
{
	if (hand[0] == hand[1])
		return true;
	else
		return false;
}

bool Player::checkDouble()
{
	if (bet > bankBalance / 2) {
		cout << "\nYou do not have a large enough balance to double";
		return false;
	}
	else
		return true;
	
}

void Player::doubledown()
{
		bet +=  bet;
}

void Player::Split(int cardThree, int cardFour)
{
	
	//get values for the players cards
	int cardOne = hand[0];
	int cardTwo = hand[1];
	
	//move the second card of the player into a new hand as the first card of a new player
	secondHand.push_back(cardTwo);
	//delete card from first hand
	hand.pop_back();

	//add one more card to each hand
	hand.push_back(cardThree);
	secondHand.push_back(cardFour);




}
