#include "Card.h"

using namespace std;

int main() {
	Deck deck;
	deck.Shuffle();
	int deckSize = deck.getDeckSize();
	while (deckSize != 0) {
		deck.drawCard();
		deckSize--;
	}
}
