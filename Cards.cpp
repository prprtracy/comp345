//yichen Huang 40167688
//comp 345 Fall 2021
//Assignment 1 Part 4
#include <iostream>
#include <algorithm>
#include <vector>
#include<string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "Cards.h"
#include "player_.h"



using namespace std;

//====================== Card ==========================//

//defualt constructor
Card::Card() {

}
//destructor
Card::~Card() {
	this->playerName = nullptr;
	this->d = nullptr;
}
void Card::play() {}

//********** Bomb **********//

Bomb::Bomb() {}//defualt constructor
Bomb::~Bomb() {}//destructor

string Bomb::getCardname() {
	return "Bomb";
}

void Bomb::play() {

	Player* player = this->playerName;
	cout << "you played card Bomb";

	this->d->insert(this);//added bomb cards back to the deck

	//delete card's owner once it has been played
	player = nullptr;
	this->playerName = nullptr;

}

//********** reinforcement **********//
reinforcement::reinforcement() {}//defualt constructor
reinforcement::~reinforcement() {}//destructor

string reinforcement::getCardname() {
	return "reinforcement";
}

void reinforcement::play() {
	Player* player = this->playerName;
	cout << "you played card reinforcement" ;
	
	this->d->insert(this);//added reinforcement cards back to the deck

	//delete card's owner once it has been played
	player = nullptr;
	this->playerName = nullptr;

}
//********** blockade **********//
blockade::blockade() {}//defualt constructor
blockade::~blockade() {}//destructor

string blockade::getCardname() {
	return "blockade";
}

void blockade::play() {

	Player* player = this->playerName;
	cout << "you played card blockade";

	this->d->insert(this);//added blockade cards back to the deck

	//delete card's owner once it has been played
	player = nullptr;
	this->playerName = nullptr;
}
//********** airlift **********//
airlift::airlift() {}//defualt constructor
airlift::~airlift() {}//destructor

string airlift::getCardname() {
	return "airlift";
}

void airlift::play() {

	Player* player = this->playerName;
	cout << "you played card airlift";

	this->d->insert(this);//added airlift cards back to the deck

	//delete card's owner once it has been played
	player = nullptr;
	this->playerName = nullptr;
}
//********** diplomacy **********//
diplomacy::diplomacy() {}//defualt constructor
diplomacy::~diplomacy() {}//destructor

string diplomacy::getCardname() {
	return "diplomacy";
}

void diplomacy::play() {

	Player* player = this->playerName;
	cout << "you played card diplomacy";
	//added bomb cards back to the deck
	this->d->insert(this);

	//delete card's owner once it has been played
	player = nullptr;
	this->playerName = nullptr;
}

//====================== Deck ==========================//

	//defualt constructor
Deck::Deck() {
	/*head = nullptr;
	tail = nullptr;
	current = nullptr;*/

	//set the cards on deck with 50 cards, 10 of each
	int decksize = 50;
	for (int i = 0; i < decksize; i++) {
		if (i < 10)
			cardsOnDeck.push_back(new Bomb());
		else if (i < 20)
			cardsOnDeck.push_back(new reinforcement());
		else if (i < 30)
			cardsOnDeck.push_back(new blockade());
		else if (i < 40)
			cardsOnDeck.push_back(new airlift());
		else
			cardsOnDeck.push_back(new diplomacy());

		cardsOnDeck[i]->d = this;
	}
}

//copy constructor
Deck::Deck(Deck& d)
{
	this->cardsOnDeck = d.cardsOnDeck;
}

//create the deck with all cards.
Deck::Deck(std::vector<Card*> newCOD) {
	this->cardsOnDeck = newCOD;
}

//destructor
Deck::~Deck() {
	for (int i = 0; i < this->cardsOnDeck.size(); i++) {
		delete this->cardsOnDeck[i];
		this->cardsOnDeck[i] = nullptr;
	}
	this->cardsOnDeck.clear();
}

//insert the card in the end of deck once it been played and removed the name of player
void Deck::insert(Card* c) {
	c->playerName = NULL;
	this->cardsOnDeck.push_back(c);
}

//this is the method to insert cards name into list of deck
/*void Deck::insert(string cardName) {

	Link addedNode = new Node;
	assert(addedNode);//try-catch to make sure node was allocated memory;
	addedNode->cardName = cardName;//add the cardname as node;

	if (head == nullptr) {//if deck is empty, then the first node becomes the head;
		head = addedNode;
	}
	else {
		tail->next = addedNode;//add new card name after the tail of list
	}
	tail = addedNode;//set the new added as the tail
	addedNode->next = nullptr;//make the addedNode as the tail;

	//delete addedNode to clean the memory
	addedNode = nullptr;
	delete addedNode;
}
*/
//this is the method to test the cards on the deck;
/*void Deck::prinList() {
	if (tail == nullptr) {//if there is no tail means the list is empty
		cout << "empty.";
	}
	else {
		Link p = new Node;
		p = head;//set the new node as the head
		while (p->next != nullptr) {
			cout << p->cardName << " ";
			p = p->next;// move the node to the next element
		}
		cout << tail->cardName << " ";//cout the last card in the list
	}
}*/

//this is the method to let player draw the cards and return a card name
/*string Deck::draw() {

	srand((unsigned int)time(NULL));
	Link p = new Node;//creat a new node
	p = head;

	//counting the number of cards remaining on deck
	int count = 0;
	while (p->next != nullptr) {
		p = p->next;
		count += 1;
	}
	count += 1;
	cout << "\nThe number of cards remaining on the deck is " << count;//testing for the count

	p = head;

	//the random function for randomly draw the card
	int n = rand() % count;
	for (int i = 0; i < n; i++) {
		p = p->next;
	}
	cout << "\nThe card you draw is : " << p->cardName << "\n";//testing print out the name of the card that been drawn

	//this is the method to removed card from deck list
	if (p == head && head->next != nullptr) {
		head = p->next;
	}
	else if (p == tail) {
		Link d = new Node;
		d = head;
		while (d->next != tail) {
			d = d->next;
		}
		tail = d;
		d->next = nullptr;
		delete d;
	}
	else {
		Link d = new Node;
		d = head;
		while (d->next != p) {
			d = d->next;
		}
		d->next = p->next;
		d = nullptr;
		delete d;
	}
	p->next = nullptr;
	string drawedCard = p->cardName;
	p = nullptr;
	delete p;

	return drawedCard;
}
*/

void Deck::draw(Player* player) {
	Hand* h = player->getHandOfPlayer();
	srand((unsigned int)time(NULL));
	int n = rand() % (this->cardsOnDeck.size() - 1);

	Card* c = this->cardsOnDeck.at(n);
	c->playerName = player;

	h->cardsOnHand.push_back(c);//add the card into hand
	this->cardsOnDeck.erase(this->cardsOnDeck.begin() + n);//remove drawed card from deck

	h = nullptr;
	c = nullptr;
}

//====================== Hand ==========================//

//defualt constructor//
Hand::Hand() {
	std::vector<Card*>cardsOnHand;
}
Hand::Hand(Player* player) {
	std::vector<Card*>cardsOnHand;
	this->player = player;
}

//copy constructor
Hand::Hand(Hand& player) {
	this->player = player.player;
	this->cardsOnHand = player.cardsOnHand;
}
//set the player on round's hand cards
Hand::Hand(Player* playerName,std::vector<Card*>COP) {
	this->player = playerName;
	this->player->setCardsOnHand(this);
	this->cardsOnHand = COP;
}


//destructor
Hand::~Hand() {
	this->player = nullptr;
}

vector<Card*> Hand::getCardsOnHand() {
	return this->cardsOnHand;
}
void Hand::remove(int n) {

	
	//find the card that already been played 
	auto cardsplayed = find(this->cardsOnHand.begin(), this->cardsOnHand.end(), this->cardsOnHand.at(0));

	//removed the card that already been played
	this->cardsOnHand.erase(cardsplayed);
}