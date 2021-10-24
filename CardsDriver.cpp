//yichen Huang 40167688
//comp 345 Fall 2021
//Assignment 1 Part 4


#include <iostream>
#include "Cards.h"
#include "player_.h"
using namespace std;
int main() {

	Card* cards;
	Deck* COD = new Deck();
	Player* player = new Player();
	Hand* h = player->getHandOfPlayer();
	//Deck cardsOnDeck;
	//Hand cardsOnHand;

	//testing the cards on the deck
	cout << "The cards remaining on the deck are :" << endl;
	for (int i = 0; i < COD->cardsOnDeck.size(); i++) {
		cout << COD->cardsOnDeck.at(i)->getCardname() << " ";
	}
	cout << endl << endl;

	cout << "The cards on your hand are :" << endl;
	//cardsOnHand.prinList();

	//testing the cards on the player's hand
	for (int i = 0; i < h->cardsOnHand.size(); i++) {
		cout << h->cardsOnHand.at(i)->getCardname() << endl;
	}

	int n = h->cardsOnHand.size();
	cout << "now you have %d cards on your hand", n;

	cout << "Now is your turn to draw the card";
	COD->draw(player);

	cout << "The cards on your hand are :";
	for (int i = 0; i < h->cardsOnHand.size(); i++) {
		cout << h->cardsOnHand.at(i)->getCardname() << endl;
	}
	int SizeOfCardsOnHand = h->cardsOnHand.size();
	cout << "now you have %d cards on your hand", SizeOfCardsOnHand;

	//cardsOnHand.prinList();
	cout << "\n";
	cout << "The cards remaining on the deck are :";
	for (int i = 0; i < COD->cardsOnDeck.size(); i++) {
		cout << COD->cardsOnDeck.at(i)->getCardname() << " ";
		if (i == 9 || i == 19 || i == 29 || i == 39) {
			cout << "\n";
		}
	}
	//cardsOnDeck.prinList();
	cout << "\n";



	return 0;
}