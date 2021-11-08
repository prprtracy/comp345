#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
	this->name = "aPlayer";
	this->orderList = new OrderList();
}

Player::Player(string str) {
	this->name = str;
	this->orderList = new OrderList();
}

Player::Player(const Player& player) {
	this->name = player.name;
	this->orderList = player.orderList;
}

Player& Player::operator=(const Player& player) {
	this->name = player.name;
	this->orderList = player.orderList;
	return *this;
}

Player::~Player() {
	this->name.clear();
	delete this->orderList;
}

void Player::toAttack() {
	cout << "This is the attack method. " << endl;
}
void Player::toDeffend() {
	cout << "This is the deffend method. " << endl;
}

void Player::issueOrder(string order) {
	if (order == "Deploy") {
		Deploy* d = new Deploy();
		orderList->add(d);
	}
	else if (order == "Advance") {
		Advance* ad = new Advance();
		orderList->add(ad);
	}
	else if (order == "Bomb") {
		BombO* bo = new BombO();
		orderList->add(bo);
	}
	else if (order == "Blockade") {
		Blockade* bl = new Blockade();
		orderList->add(bl);
	}
	else if (order == "Airlift") {
		Airlift* ai = new Airlift();
		orderList->add(ai);
	}
	else if (order == "Negotiate") {
		Negotiate* n = new Negotiate();
		orderList->add(n);
	}
	else {
		Orders* o = new Orders(order);
		orderList->add(o);
	}
}

string Player::get_name() {
	return this->name;
}

OrderList* Player::get_orderList() {
	return this->orderList;
}

void Player::print_orderList() {
	this->orderList->print_ol();
}

Hand* Player::getHandOfPlayer() {
	return this->hand;
}

void Player::setCardsOnHand(Hand* hand) {
	this->hand = hand;
}

vector<Territory*> Player::getTerritories()
{
    vector<Territory*> t = this->territories;

    return t;
}

