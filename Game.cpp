#include<iostream>
#include<vector>
#include<memory>

#include "Game.h"
#include "Dealer.h"
#include "Player.h"
#include "Card.h"
#include "cardsGraphics.h"
#include "fssimplewindow.h"

using namespace std;


int Game::playHand() {

	//Display Current rules
	//displayRules();

	//initialize bank balance
	thePlayer.setBankBalance(100);

	//set whether the dealer will stand or hit on soft 17 
	// will add once i figure out the soft and hard aces and add dealer AI
	//theDealer.setLevel();


	//Start the game and repeat while Player wants to or is able to 
	while (play == true) {

		int mouseEvent, leftButton, middleButton, rightButton;
		int locX, locY;

		

		//initialize deck and bank balance
		theDeck.Shuffle();
		playerBust = false;
		player2ndBust = false;
		dealerBust = false;
		splitty = false;
		splitOcurred = false;
		//betInsurance = false;

		//ask user for bet amount
		betAmount();

		//
		DealerDeck.push_back(theDeck.drawCard());
		addDealerCardCount();
		theDealer.Hit(theDeck.getCardValue(DealerDeck[dealerCardCount]->getCardNumber()));

		PlayerDeck.push_back(theDeck.drawCard());
		addPlayerCardCount();
		thePlayer.Hit(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));

		DealerDeck.push_back(theDeck.drawCard());
		addDealerCardCount();
		theDealer.Hit(theDeck.getCardValue(DealerDeck[dealerCardCount]->getCardNumber()));

		PlayerDeck.push_back(theDeck.drawCard());
		addPlayerCardCount();
		thePlayer.Hit(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));

		//deal hands will use card and deck class but for now will assign
		//random cards to test logic
		/*theDealer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
		thePlayer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
		theDealer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
		thePlayer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));*/

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		printBackground(1280, 720);
		//Display Hands
		//theDealer.displayCards(true);
		displayCards(true);

		thePlayer.getHandValue();
		bool InsuranceLoop = false;
		char Insurance;



		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, locX, locY);

		if (locX >= 1109 && locX <= 1274 && locY >= 5 && locY <= 45) { //Quit button
			if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
				play = false;
				return 0;
			}
		}



		//ask user if they want insurance if the dealer has an ace
		if (theDealer.getCardValue(1) == 11) {
			while (InsuranceLoop == false) {

				cout << "\nThe dealer is showing an Ace. Would you like insurance (Y/N)? " << endl;
				cin >> Insurance;
				cout << "\n" << endl;

				if (Insurance == 'Y' || Insurance == 'y') {
					betInsurance = true;
					thePlayer.subBankBalance(thePlayer.getBet() / 2);
					InsuranceLoop = true;
				}
				else if (Insurance == 'N' || Insurance == 'n') {
					betInsurance = false;
					InsuranceLoop = true;
				}
				else
					InsuranceLoop = false;
			}
		}

		//Check for immediate win
		immediateWin();


		//start loop if blackjack hasnt happened
		if (initialblackjack == false) {

			bool Split = thePlayer.checkSplit();
			bool Duble = thePlayer.checkDouble();
			bool userInput = false;
			string input;

			int once_1 = 0;
			while (userInput == false) {
				//ask user for their choice 

				if (once_1 == 0) {
					cout << endl << "\nWould you like to Hit, Double, or Stand? Please select the button on the game window.";
					once_1 = 1;
				}


				bool mouse_selection_1 = false;

				while (mouse_selection_1 == false) {

					mouseEvent = FsGetMouseEvent(leftButton, middleButton,
						rightButton, locX, locY);

					if (locX >= 1109 && locX <= 1274 && locY >= 5 && locY <= 45) { //Quit button
						if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
							play = false;
							return 0;
						}
					}

					else if (locX >= 8 && locX <= 220 && locY >= 652 && locY <= 702) {
						if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
							input = "h";
							mouse_selection_1 = true;
						}
					}
					else if (locX >= 522 && locX <= 733 && locY >= 652 && locY <= 702) {
						if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
							input = "d";
							mouse_selection_1 = true;
						}
					}
					//else if (locX >= 1060 && locX <= 1272 && locY >= 652 && locY <= 702) {
					//	if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
					//		input = "p";
					//		mouse_selection_1 = true;
					//	}
					//}
					else if (locX >= 1060 && locX <= 1272 && locY >= 652 && locY <= 702) {
						if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
							input = "s";
							mouse_selection_1 = true;
						}
					}
				}




				if (input == "h" /* || input = "H" */) {
					draw = true;
					userInput = true;
				}
				else if (input == "d" /* || input = "D"*/) {
					if (Duble == true) {
						PlayerDeck.push_back(theDeck.drawCard());
						addPlayerCardCount();
						thePlayer.Hit(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));
						//thePlayer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
						thePlayer.doubledown();
						//thePlayer.displayCards();
						displayCards(true);
						thePlayer.getHandValue();
						//checkSoftOrHard();
						decideSoftorHard();

						draw = false;
						userInput = true;
					}
					else {
						cout << "Unable to Double";
						userInput = false;
					}
				}

				else if (input == "p" /* || input = "P"*/) {
					if (Split == true) {
						//creates second hand and populates both hands to full size
						PlayerDeck.push_back(theDeck.drawCard());
						addPlayerCardCount();
						int cardThree = theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber());
						PlayerDeck.push_back(theDeck.drawCard());
						addPlayerCardCount();
						int cardFour = theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber());
						thePlayer.Split(cardThree, cardFour);
						//thePlayer.doubledown();
						splitty = true;
						userInput = true;
						splitOcurred = true;
					}
				}

				else if (input == "s" /* || input = "S"*/) {
					draw = false;
					userInput = true;
				}
			}

			//enter into a different loop to handle the user now having two hands instead of one
			while (splitty == true) {

				//Display Hands
				//theDealer.displayCards(true);
				//thePlayer.displayCards();
				displayCards(true);
				thePlayer.getHandValue();
				thePlayer.display2nd();
				thePlayer.get2ndValue();

				//play first hand
				bool splitInput = false;
				int once_2 = 0;
				while (splitInput == false) {
					//ask user for their choice 

					if (once_2 == 0) {
						cout << endl << "\nWould you like to Hit, Double, or Stand? Please select the button on the game window.";
						once_2 = 1;
					}

					//int mouseEvent, leftButton, middleButton, rightButton;
					//int locX, locY;

					bool mouse_selection_2 = false;

					while (mouse_selection_2 == false) {

						mouseEvent = FsGetMouseEvent(leftButton, middleButton,
							rightButton, locX, locY);

						if (locX >= 1109 && locX <= 1274 && locY >= 5 && locY <= 45) { //Quit button
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								play = false;
								return 0;
							}
						}
						
						else if (locX >= 8 && locX <= 220 && locY >= 652 && locY <= 702) {
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								input = "h";

								mouse_selection_2 = true;
							}
						}
						else if (locX >= 522 && locX <= 733 && locY >= 652 && locY <= 702) {
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								input = "d";
								mouse_selection_2 = true;
							}
						}
						//else if (locX >= 1060 && locX <= 1272 && locY >= 652 && locY <= 702 && mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
						//	input = "p";
						//}
						else if (locX >= 1109 && locX <= 1274 && locY >= 652 && locY <= 702) {
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								input = "s";
								mouse_selection_2 = true;
							}
						}
					}


					//cin >> input;
					//cout << "\n" << endl;

					if (input == "h" /* || input = "H" */) {
						draw = true;
						while (draw == true) {

							//deal player another card
							PlayerDeck.push_back(theDeck.drawCard());
							addPlayerCardCount();
							thePlayer.Hit(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));
							//thePlayer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));

							//display new set of cards
							//thePlayer.displayCards();
							displayCards(true);
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
						splitInput = true;
						splitty = false;
						draw = false;
					}
					else if (input == "d" /* || input = "D"*/) {
						if (Duble == true) {
							PlayerDeck.push_back(theDeck.drawCard());
							addPlayerCardCount();
							thePlayer.Hit(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));
							//thePlayer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
							thePlayer.doubledown();
							//thePlayer.displayCards();
							displayCards(true);
							thePlayer.getHandValue();
							//checkSoftOrHard();
							decideSoftorHard();

							draw = false;
							splitInput = true;
						}
						else {
							cout << "Unable to Double";
							splitInput = false;
						}
					}

					else if (input == "s" /* || input = "S"*/) {
						draw = false;
						splitInput = true;
						splitty = false;
					}

				}

				splitInput = false;
				int once_3 = 0;
				while (splitInput == false) {
					//play second hand
					//ask user for their choice 
					if (once_3 == 0) {
						cout << endl << "\nWould you like to Hit, Double, or Stand on your second hand? Please select the button on the game window.";
						once_3 = 1;
					}
					//cin >> input;
					//cout << "\n" << endl;


					bool mouse_selection_3 = false;

					while (mouse_selection_3 == false) {

						mouseEvent = FsGetMouseEvent(leftButton, middleButton,
							rightButton, locX, locY);

						if (locX >= 1109 && locX <= 1274 && locY >= 5 && locY <= 45) { //Quit button
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								play = false;
								return 0;
							}
						}
						else if (locX >= 8 && locX <= 220 && locY >= 652 && locY <= 702) {
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								input = "h";
								mouse_selection_3 = true;
							}
						}
						else if (locX >= 522 && locX <= 733 && locY >= 652 && locY <= 702) {
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								input = "d";
								mouse_selection_3 = true;
							}
						}
						//else if (locX >= 1060 && locX <= 1272 && locY >= 652 && locY <= 702) {
						//	if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
						//		input = "p";
						//		mouse_selection_3 = true;
							//}
						//}
						else if (locX >= 1109 && locX <= 1274 && locY >= 652 && locY <= 702) {
							if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
								input = "s";
								mouse_selection_3 = true;
							}
						}
					}

					if (input == "h" /* || input = "H" */) {
						draw = true;
						while (draw == true) {

							//deal player another card
							PlayerDeck.push_back(theDeck.drawCard());
							addPlayerCardCount();
							thePlayer.Hit2nd(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));
							//thePlayer.Hit2nd(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));

							//display new set of cards
							thePlayer.display2nd();
							thePlayer.get2ndValue();

							//decide aces being soft or hard
							decideSoftorHard2nd();

							//check bust
							checkBust2nd();

							//check win
							blackJack();

							//make sure the user can hit
							if (thePlayer.Check2ndHand() < 21) {
								//ask user wants hit
								playerWantsHit();
							}
						}
						splitInput = true;
						draw = false;
						splitty = false;
					}
					else if (input == "d" /* || input = "D"*/) {
						if (Duble == true) {
							PlayerDeck.push_back(theDeck.drawCard());
							addPlayerCardCount();
							thePlayer.Hit2nd(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));
							//thePlayer.Hit2nd(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
							thePlayer.doubledown();
							thePlayer.display2nd();
							thePlayer.get2ndValue();
							//checkSoftOrHard2nd();
							decideSoftorHard2nd();

							draw = false;
							splitInput = true;
							splitty = false;
						}
						else {
							cout << "Unable to Double";
							splitInput = false;
						}
					}

					else if (input == "s" /* || input = "S"*/) {
						draw = false;
						splitInput = true;
						splitty = false;
					}
				}
				splitOcurred = true;
			}

			//if player chose another card and has not splitted
			while (draw == true) {

				//deal player another card
				PlayerDeck.push_back(theDeck.drawCard());
				addPlayerCardCount();
				thePlayer.Hit(theDeck.getCardValue(PlayerDeck[playerCardCount]->getCardNumber()));
				//thePlayer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));

				//display new set of cards
				//thePlayer.displayCards();
				displayCards(true);
				thePlayer.getHandValue();

				//decide aces being soft or hard
				decideSoftorHard();

				//check bust
				checkBust();

				//check win
				//blackJack();

				//make sure the user can hit
				if (thePlayer.CheckHand() < 21) {
					//ask user wants hit
					playerWantsHit();
				}
				else
					draw = false;
			}


			//make sure the user did not bust
			if (thePlayer.CheckHand() <= 21) {

				//Dealer needs to hit now unless split occurred then hit later
				if (splitOcurred == false)
					hitUntilStand();

				//checkBust
				checkBust();

				//check blackjack
				//blackJack();
			}
			//if the user splitted need to check the second hand
			if (splitOcurred == true) {

				//dealer needs to hit
				hitUntilStand();

				//check 2nd bust
				checkBust2nd();

			}
			//compare scores if no one went bust or got blackjack
			if ((playerBust == false) && (dealerBust == false) && (playerHasBlackjack == false)) {
				whoWins();

			}
			if (splitOcurred == true && player2ndBust == false)
				whoWins2nd();
		}
		//display cardds
		displayCards(false);
		//erase hands
		thePlayer.eraseHand();
		theDealer.eraseHand();
		clearDecks();
		dealerCardCount = -1;
		playerCardCount = -1;
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
	return 0;
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
		thePlayer.addBankBalance(1.5 * thePlayer.getBet());
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
	else if ((playerScore != 21) && (dealerScore == 21)) {
		cout << "\n";
		cout << "The Dealer has Blackjack. You lose" << endl;
		draw = false;
		initialblackjack = true;

		if (betInsurance == false)
			thePlayer.subBankBalance(thePlayer.getBet());
		else
			thePlayer.addBankBalance(thePlayer.getBet() / 2);
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

	while (thePlayer.getBet() > thePlayer.getBankBalance()) {
		cout << "\nYou do not have enough money to make that bet.";
		cout << "\nGambling Problem? Call 1-800-GAMBLER for assistance";
		betAmount();

	}
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

void Game::decideSoftorHard2nd()
{
	if (thePlayer.Check2ndHand() > 21) {
		//this will fail if someone does not enter a 1 or 11 but this is a start
		int handSize = thePlayer.get2ndSize();
		int newCardValue;
		//check cards in players hand
		for (int i = 0; i < handSize; i++) {
			int cardValue = thePlayer.get2ndValue(i);
			if (cardValue == 11) {
				cout << "\nWould you like your ace to be valued at 1 or 11: ";
				cin >> newCardValue;
				thePlayer.set2ndValue(i, newCardValue);
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
		cout << "You bust" << endl;
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

void Game::checkBust2nd() {
	//Define local variables.
	int playerScore = thePlayer.Check2ndHand();
	int dealerScore = theDealer.CheckHand();

	//Check if Player busts. 
	if (playerScore > 21)
	{
		cout << "\n" << endl;
		cout << "You bust" << endl;
		cout << "\n" << endl;
		draw = false;
		player2ndBust = true;
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
			DealerDeck.push_back(theDeck.drawCard());
			addDealerCardCount();
			theDealer.Hit(theDeck.getCardValue(DealerDeck[dealerCardCount]->getCardNumber()));
			//theDealer.Hit(theDeck.getCardValue(theDeck.drawCard()->getCardNumber()));
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
	if (playerScore < 22 && (playerScore > dealerScore) ||
		(dealerScore > 21) && (playerScore < 22)) {

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

void Game::whoWins2nd() {

	int playerScore = thePlayer.Check2ndHand();
	int dealerScore = theDealer.CheckHand();

	//Player win 
	if (playerScore < 22 && (playerScore > dealerScore) ||
		(dealerScore > 21) && (playerScore < 22)) {

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
	else if (Play == 'n' || Play == 'N') {

		play = false;

	}
	else {
		cout << "\nPlease enter your choice using the Y or N keys.";
		playAnotherHand();
	}
}

void Game::playerWantsHit() {

	string Draw;

	int mouseEvent, leftButton, middleButton, rightButton;
	int locX, locY;

	bool mouse_selection = false;

	//ask user for input
	cout << endl << "\nWould you like to Hit or Stand? Please select the button on the game window.";

	while (mouse_selection == false) {

		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, locX, locY);


		if (locX >= 8 && locX <= 220 && locY >= 652 && locY <= 702) {
			if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
				//Draw = "h";
				draw = true;
				mouse_selection = true;
			}
		}
		else if (locX >= 1109 && locX <= 1274 && locY >= 652 && locY <= 702) {
			if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || leftButton) {
				//Draw = "s";
				draw = false;
				mouse_selection = true;
			}
		}

	}
	////If they do, return true and start the loop to draw another card.
	//if (Draw == 'h' || Draw == 'H') {
	//	draw = true;
	//}
	////If they don't, skip the loop. 
	//else if (Draw == 's' || Draw == 'S')
	//{
	//	draw = false;
	//}
	//else {
	//	cout << "\nPlease enter your choice using the Hit or Stand buttons.";
	//	playerWantsHit();
	//}
}

void Game::displayCards(bool isDealer) {

	printCards(DealerDeck, 575, 20, isDealer);

	printCards(PlayerDeck, 575, 475, false);

	FsSwapBuffers();



}