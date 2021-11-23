#pragma once
#include <memory> // unique_ptr
#include <vector>
using namespace std;

// Card Class
class Card {
public:
	// Enum for cards' suits, easy to use integers for assignment
	enum Suit : unsigned char
	{
		diamond, clover, heart, spade
	};

private:
	// Every card should have a number (1-13) and suit (look at enums) (I'll have to deal with face cards later)
	unsigned int number;
	Suit suit;

public:
	// Constructor for a Card object instantiation, takes in a number and a suit encoded as an integer
	Card(unsigned int num, Suit s) : number(num), suit(s) {}

public:
	// Member functions to access private variables
	unsigned int getCardNumber() { return number; }
	Suit getCardSuit() { return suit; }
};


// Deck Class
class Deck {
private:
	/* Deck is just a vector of cards. I chose to use card pointers for the sake of flexibility. If I don't use pointers, the deck gets destroyed at the end of a function, but I foresee us calling Deck in many places. */
	vector<Card*> theDeck;

private:
	// Swaping one card with another card
	void Swap(Card*& left, Card*& right) {
		auto temp = left;
		left = right;
		right = temp;
	}

public:
	// Constructor for ONE deck of card (for now)
	Deck() {
		theDeck.reserve(52); // If we expand to more decks, this number has to change
		for (int i = 1; i <= 13; i++) { // Loop through all possible card numbers
			for (int j = 0; j < 4; j++) { // Loop through all possible suits
				/* 1. Card(arg1, arg2) = Constructing a card through assigning 2 arguments, refer to Card class constructor.
				   2. unique_ptr<Card>(new Card(...)) = Make a unique pointer for a new Card object, "unique" prevents memory overwriting.
				   3. emplace_back(...) = More memory efficient function compared to push_back, push_back will make a copy of the argument you're passing in before shoving into the vector, where emplace_back will not.*/
				theDeck.emplace_back(unique_ptr<Card>(new Card(i, static_cast<Card::Suit>(j))));
			}
		}
	}

public:
	// Member function to get private variable's information
	int getDeckSize() { return theDeck.size(); }

	// Shuffles the deck (See Card.cpp)
	void Shuffle();

	// Draw a card at the top (back of the vector) of the deck (See Card.cpp)
	int drawCard();
};