

#include<iostream>
#include<vector>
#include<memory>

#include "Game.h"
#include "Dealer.h"
#include "Player.h"
#include "Card.h"

using namespace std;



void Game::playHand() {

	//Display Current rules
	displayRules();

	//initialize bank balance
	thePlayer.setBankBalance(100);

	//set whether the dealer will stand or hit on soft 17 
	// will add once i figure out the soft and hard aces and add dealer AI
	//theDealer.setLevel();

	
	//Start the game and repeat while Player wants to or is able to 
	while (play == true) {

		//initialize deck and bank balance
		theDeck.Shuffle();
		playerBust = false;
		dealerBust = false;

		//ask user for bet amount
		betAmount();
		while (thePlayer.getBet() > thePlayer.getBankBalance()) {
			cout << "\nYou do not have enough money to make that bet.";
			cout << "\nGambling Problem? Call 1-800-GAMBLER for assistance";
			betAmount();

		}

		//deal hands will use card and deck class but for now will assign
		//random cards to test logic
		theDealer.Hit(theDeck.drawCard());
		thePlayer.Hit(theDeck.drawCard());
		theDealer.Hit(theDeck.drawCard());
		thePlayer.Hit(theDeck.drawCard());
		
		//Display Hands
		theDealer.displayCards(true);
		thePlayer.displayCards();
		thePlayer.getHandValue();

		//Check for immediate win
		immediateWin();

		//Check whether the user would like their ace to be soft or hard
		//decideSoftOrHard();

		//start loop if blackjack hasnt happened
		if (initialblackjack == false) {

			bool Split = thePlayer.checkSplit();
			bool Duble = thePlayer.checkDouble();
			bool userInput = false;
			string input;

			while (userInput == false) {
				//ask user for their choice 
				cout << endl << "\nWould you like to Hit, Double, Split, or Stand? (H/D/P/S) ";
				cin >> input;
				cout << "\n" << endl;

				if (input == "h" /* || input = "H" */) {
					draw = true;
					userInput = true;
				}
				else if (input == "d" /* || input = "D"*/) {
					if (Duble == true) {
						thePlayer.Hit(theDeck.drawCard());
						thePlayer.doubledown();
						thePlayer.displayCards();
						thePlayer.getHandValue();
						draw = false;
						userInput = true;
					}
					else {
						cout << "Unable to Double";
						userInput = false;
					}
				}

				else if (input == "p" /* || input = "P"*/) {
					if (Split == true)
						thePlayer.Split();

				}

				else if (input == "s" /* || input = "S"*/) {
					draw = false;
					userInput = true;
				}
			}

			//see if user wants to hit
			//playerWantsHit();

			//if player chose another card
			while (draw == true) {

				//deal player another card
				thePlayer.Hit(theDeck.drawCard());

				//display new set of cards
				thePlayer.displayCards();
				thePlayer.getHandValue();

				//decide aces being soft or hard
				decideSoftorHard();

				//check bust
				checkBust();

				//check win
				blackJack();

				//make sure the user can hit
				if (thePlayer.CheckHand() < 21) {
					//ask user wants hit
					playerWantsHit();
				}
			}


			//make sure the user did not bust
			if (thePlayer.CheckHand() < 21) {

				//Dealer needs to hit now
				hitUntilStand();

				//checkBust
				checkBust();

				//check blackjack
				//blackJack();
			}
			//compare scores if no one went bust or got blackjack
			if ((playerBust == false) && (dealerBust == false) && (playerHasBlackjack == false)) {
				whoWins();
			}
		}
		//erase hands
		thePlayer.eraseHand();
		theDealer.eraseHand();
		addHands();


		//ask user if they would like to play again if they have any money
		if (thePlayer.getBankBalance() > 0) {
			playAnotherHand();
		}
		else {
			cout << "\nYou have run out of money. Thank you for playing.";
			cout << "\nGambling Problem? Call 1-800-GAMBLER for assistance";
			play = false;
		}

		
	}
	displayStats();
}

void Game::displayRules()
{
	cout << "Welcome to our game of blackjack";
	cout << "\nThe goal of blackjack is to beat the dealer's hand without going over 21."
		"\nEach player starts with two cards, one of the dealer's cards is hidden until the end."
		"\nTo 'Hit' is to ask for another card.To 'Stand' is to hold your total and end your turn."
		"\nIf you go over 21 you bust, and the dealer wins regardless of the dealer's hand."
		"\nIf you are dealt 21 from the start(Ace & 10), you got a blackjack."
		"\nDealer will hit until their cards total 17 or higher."
		"\nGood Luck!\n";

}

//void Game::intializeDeck() {//used for testing logic
//	int Ace = 11;
//	int J = 10;
//	int Q = 10;
//	int K = 10;
//	
//	deck = {
//			Ace,2,3,4,5,6,7,8,9,10,J,Q,K,
//			Ace,2,3,4,5,6,7,8,9,10,J,Q,K,
//			Ace,2,3,4,5,6,7,8,9,10,J,Q,K,
//			Ace,2,3,4,5,6,7,8,9,10,J,Q,K
//	};
//}
//
//void Game::shuffla() {//used for testing logic
//	srand((unsigned)time(0));
//	for (int i = 0; i < 52; i++)
//		swap(deck[i], deck[rand() % 52]);
//	
//}
//
//int Game::getCard() {
//	int card = deck.front();
//	deck.erase(deck.begin());
//	return card;
//}

void Game::immediateWin() {
	int playerScore = thePlayer.CheckHand();
	int dealerScore = theDealer.CheckHand();

	if ((playerScore == 21) && (dealerScore != 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.

		cout << "\n";
		cout << "Blackjack! You win!" << endl;
		draw = false;
		initialblackjack = true;
		addWins();
		thePlayer.addBankBalance(thePlayer.getBet());
	}
	//If both Player and Dealer have blackjack. 
	else if ((playerScore == 21) && (dealerScore == 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.
		cout << "\n";
		cout << "The Dealer and you both got Blackjack. Push" << endl;
		draw = false;
		initialblackjack = true;
		
	}
	//dealer has blackjack
	else if ((playerScore!=21) && (dealerScore==21)) {
		cout << "\n";
		cout << "The Dealer has Blackjack. You lose" << endl;
		draw = false;
		initialblackjack = true;
		thePlayer.subBankBalance(thePlayer.getBet());
	}
	else {//continue with game
		initialblackjack = false;
	}
}

void Game::displayStats()
{
	cout << "\nYou won " << wins << " hands of blackjack out of " << totHands << endl;
	cout << "\nEnding bank balance: " << thePlayer.getBankBalance() << "\n" << endl;
}

void Game::betAmount()
{
	int bet;
	//display current bank amount
	cout << "\nCurrent bank balance: " << thePlayer.getBankBalance();
	//ask user how much they would like to bet on this hand
	cout << "\nPlease enter a bet amount for the following hand: ";
	cin >> bet;

	
	thePlayer.setBet(bet);
}

void Game::decideSoftorHard()
{
	if (thePlayer.CheckHand() > 21) {
		//this will fail if someone does not enter a 1 or 11 but this is a start
		int handSize = thePlayer.getHandSize();
		int newCardValue;
		//check cards in players hand
		for (int i = 0; i < handSize; i++) {
			int cardValue = thePlayer.getCardValue(i);
			if (cardValue == 11) {
				cout << "\nWould you like your ace to be valued at 1 or 11: ";
				cin >> newCardValue;
				thePlayer.setCardValue(i, newCardValue);
			}
		}
	}

}

void Game::intelligentHand()
{
	int handSize = theDealer.getHandSize();
	int newCardValue;
	
	//check if ace is in dealers hand
	bool AceCheck = theDealer.checkAce();

	//if dealer has an ace change it to 1 point if it will beat the player
	if (AceCheck != false) {
		if (theDealer.CheckHandAce() > thePlayer.CheckHand()) {

			//make sure dealer doesnt bust
			if (theDealer.CheckHandAce() < 22) {

				//find the ace and set it to 1
				//check cards in dealers hand
				for (int i = 0; i < handSize; i++) {
					int cardValue = theDealer.getCardValue(i);

					if (cardValue == 11) 
						theDealer.setCardValue(i, 1);
					
				}
			}
		}
		//if hand is a bust set value to 1
		else if (theDealer.CheckHand() > 21) {

			for (int i = 0; i < handSize; i++) {
				int cardValue = theDealer.getCardValue(i);
				
				if (cardValue == 11) {
					theDealer.setCardValue(i, 1);
				}
			}
		}
	}
		
}

void Game::checkSoftOrHard()
{//this will fail if someone does not enter a 1 or 11 but this is a start
	int handSize = thePlayer.getHandSize();
	int newCardValue;
	//check cards in players hand
	for (int i = 0; i < handSize; i++) {
		int cardValue = thePlayer.getCardValue(i);
		if (cardValue == 11) {
			cout << "\nYour potential hand values are:  ";
			cin >> newCardValue;
			thePlayer.setCardValue(i, newCardValue);
		}
	}

}

void Game::blackJack() {
	int playerScore = thePlayer.CheckHand();
	int dealerScore = theDealer.CheckHand();

	if ((playerScore == 21) && (dealerScore != 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.

		cout << "\n";
		cout << "Blackjack! You win!" << endl;
		draw = false;
		playerHasBlackjack = true;
		addWins();
		thePlayer.addBankBalance(thePlayer.getBet());
	}
	//If both Player and Dealer have blackjack. 
	else if ((playerScore == 21) && (dealerScore == 21))
	{
		//Display message, compute new winnings multiplier, ask to play another hand.
		cout << "\n";
		cout << "The Dealer and you both got Blackjack. Push" << endl;
		draw = false;
		playerHasBlackjack = true;
	}
	else if ((playerScore != 21) && (dealerScore == 21))
	{
		
		cout << "\n";
		cout << "The Dealer has Blackjack. You Lose" << endl;
		draw = false;
		playerHasBlackjack = true;
		thePlayer.subBankBalance(thePlayer.getBet());
	}
	else {
		playerHasBlackjack = false;
	}

}

void Game::checkBust() {
	//Define local variables.
	int playerScore = thePlayer.CheckHand();
	int dealerScore = theDealer.CheckHand();

	//Check if Player busts. 
	if (playerScore > 21)
	{
		cout << "\n" << endl;
		cout << "You bust"  << endl;
		cout << "\n" << endl;
		draw = false;
		playerBust = true;
		thePlayer.subBankBalance(thePlayer.getBet());
	}

	//Check if Dealer busts.
	//Display message, compute new winnings multiplier, ask to play another hand.
	else if (dealerScore > 21)
	{
		cout << "\n" << endl;
		cout << "The Dealer went bust. You Win!" << endl;
		cout << "\n" << endl;
		draw = false;
		dealerBust = true;
		addWins();
		thePlayer.addBankBalance(thePlayer.getBet());
	}
}

void Game::hitUntilStand() {
	
	int handSize = theDealer.getHandSize();

	for (int i = 0; i < handSize; i++) {
		int dealerScore = theDealer.CheckHand();
		if (dealerScore < 17) {
			theDealer.Hit(theDeck.drawCard());
			intelligentHand();
		}
		handSize = theDealer.getHandSize();
		
	}
	theDealer.displayCards(false);
}

void Game::whoWins() {

	int playerScore = thePlayer.CheckHand();
	int dealerScore = theDealer.CheckHand();

	//Player win 
	if (playerScore < 22 && (playerScore>dealerScore) || 
		(dealerScore>21) && (playerScore<22)) {

		cout << "\n";
		cout << "Dealer score: " << dealerScore;
		cout << "\nPlayer score: " << playerScore;
		cout << "\nYou win!" << endl;
		draw = false;
		addWins();
		thePlayer.addBankBalance(thePlayer.getBet());
	

	}
	else {//Tie
		if (playerScore == dealerScore) {
			cout << "\n";
			cout << "Dealer score: " << dealerScore;
			cout << "\nPlayer score: " << playerScore;
			cout << "\nPush" << endl;
			draw = false;
	
		}
		else {
			cout << "\n";
			cout << "Dealer score: " << dealerScore;
			cout << "\nPlayer score: " << playerScore;
			cout << "\nYou lose." << endl;
			draw = false;
			thePlayer.subBankBalance(thePlayer.getBet());
		
		}
	}
}

void Game::playAnotherHand() {
	//ask user if they want to play again
	char Play;
	cout << endl << "\nWould you like to play another hand? (Y/N) ";
	cin >> Play;
	cout << "\n" << endl;

	//Go back to the main game logic function to restart if they do. 
	if (Play == 'y' || Play == 'Y') {
		
		play = true;
	}
	//If they don't, exit the program.
	else if(Play=='n'|| Play=='N'){
		
		play = false;
		
	}
	else {
		cout << "\nPlease enter your choice using the Y or N keys.";
		playAnotherHand(); 
	}
}

void Game::playerWantsHit() {

	char Draw;
	//ask user for input
	cout << endl << "\nWould you like to hit or stand? (H/S) ";
	cin >> Draw;
	cout << "\n";

	//If they do, return true and start the loop to draw another card.
	if (Draw == 'h' || Draw == 'H'){
		draw = true;
	}
	//If they don't, skip the loop. 
	else if(Draw=='s'|| Draw=='S')
	{
		draw = false;
	}
	else {
		cout << "\nPlease enter your choice using the H or S keys.";
		playerWantsHit();
	}
}

