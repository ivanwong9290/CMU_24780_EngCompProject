#include <iostream>
#include <vector>
#include <ctime> // rand, srand
#include "Card.h"

using namespace std;

void Deck::Shuffle()
{
	// This is necessary for the random number generator
	srand(time(nullptr));
	int deckSize = getDeckSize();

	// Sequentially swap until the end of deck = shuffling
	for (int i = 0; i < deckSize; i++) {
		int r = rand() % deckSize;
		Swap(theDeck[i], theDeck[r]);
	}
}

int Deck::drawCard()
{
	if (!theDeck.empty()) {
		// Grab the last card in the deck
		Card* currCard = theDeck.back();
		// Show information (Can replace this with actual functionality later on)
		cout << "CARDS REMAINING: " << getDeckSize() << ", " << currCard->getCardNumber() << " of " << currCard->getCardSuit() << endl;
		// Erase the card that was drawn
		theDeck.pop_back();
		return currCard->getCardNumber();
	}
	cout << "Deck is empty." << endl;
}