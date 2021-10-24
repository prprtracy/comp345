//yichen Huang 40167688
//comp 345 Fall 2021
//Assignment 1 Part 4
#pragma once

#ifndef _Hand_HEADER
#define _Hand_HEADER


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include "Player.h"
#define max 5


using namespace std;

class Deck;
class Player;
//====================== Card ==========================//
class Card {
public:
	Player* playerName;
	Deck* d;

	Card();//defualt constructor
	virtual ~Card();

	//accessors and mutators
	virtual string getCardname() = 0;
	virtual void play() = 0;
};
class Bomb :public Card {
public:
	Bomb();//defualt constructor
	~Bomb();//destructor

	string getCardname();
	void play();
};
class reinforcement :public Card {
public:
	reinforcement();//defualt constructor
	~reinforcement();//destructor

	string getCardname();
	void play();
};
class blockade :public Card {
public:
	blockade();//defualt constructor
	~blockade();//destructor

	string getCardname();
	void play();
};
class airlift :public Card {
public:
	airlift();//defualt constructor
	~airlift();//destructor

	string getCardname();
	void play();
};
class diplomacy :public Card {
public:
	diplomacy();//defualt constructor
	~diplomacy();//destructor

	string getCardname();
	void play();
};


//====================== Deck ==========================//

class Deck {
/*private:
	struct Node;
	typedef Node* Link;
	struct Node {
		string cardName;
		Link next;
	};
	Link head;
	Link tail;
	Link current;*/
protected:
public:

	std::vector<Card*> cardsOnDeck;//set the card on deck belong to deck
	Deck();//default constructor
	Deck(Deck& d);//copy constructor
	Deck(std::vector<Card*> cardsOnDeck);
	~Deck();//destructor
	void insert(Card* c);//insert the card on the deck
	//void insert(string cardName);
	//void prinList();
	void draw(Player* player);
};



//====================== Hand ==========================//

class Hand {
protected:
	Player* player;
public:
	std::vector<Card*> cardsOnHand;//set the card on hand belong to hand
	Hand();//default constructor
	Hand(Player* player);
	Hand(Hand& player);
	Hand(Player* playerName, std::vector<Card*> cardsOnPlayerHand);
	~Hand();//destructor
	std::vector<Card*>getCardsOnHand();
	void remove(int n);//removed the cards from the Hand

	//void prinList();
};
#endif // !Hand_HEADER
