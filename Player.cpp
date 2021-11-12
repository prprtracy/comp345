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
		/*Orders* o = new Orders(order);
		orderList->add(o);*/
		cout << "Invalid order. Valid order Types: 1. Deploy, 2. Advance, 3. Bomb, 4. Blockade, 5 Airlift, 6. Negotiate." << endl;
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

// return neighboring territories
vector<Territory*> Player::toAttack()
{
    cout << "Territories to attack: " << endl;
    vector<Territory*> attackList;
    Territory* t = nullptr;
    for (int i = 0; i < this->territories.size(); i++) // for each of this Player's Territories
    {
        t = this->territories.at(i);
        for (int j = 0; j < t->allAdjTerritories.size(); j++) // for each of that Territories asjacent Territories
        {
            if (t->allAdjTerritories.at(j)->getOwner() != this) // if this Player does not own that Territory
            {
                if (!(t->allAdjTerritories.at(j)->haveTerritory(attackList))) // if Territory is not alredy in list
                {
                    attackList.push_back(t->allAdjTerritories.at(j));
                    cout<<territories.at(j)->get_name()<<endl;
                }
            }
        }
    }

    return attackList;
}

//return the list
vector<Territory*> Player::toDefend()
{
    cout << "Territories to defend: " << endl;

    vector<Territory*> defendList;
    for (int i = 0; i < this->territories.size(); i++)
    {
        defendList.push_back(this->territories.at(i));
        cout<<territories.at(i)->get_name()<<endl;
    }

    return defendList;
}

bool Player::isLost()
{
    return this->eliminated;
}

// Sets this Player's eliminated data member to true.
void Player::setLostPlayer()
{
    this->eliminated = true;
}

void Player::increaseReinforcementPool(int armies) {
	this->reinforcementPool += armies;
}
void Player::decreaseReinforcementPool(int armies) {
	this->reinforcementPool -= armies;
}
