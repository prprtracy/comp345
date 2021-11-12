#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
    this->name = "aPlayer";
    this->orderList = new OrderList();
    this->playerNumber =0;
    this->hand = new Hand(this);
    this->orderList = new OrderList();
    this->reinforcementPool = 0;
    this->eliminated = false;
    vector<Territory*> terr;
    this->territories = terr;
}

Player::Player(string str) {
	this->name = str;
	this->orderList = new OrderList();
}

Player::Player(const Player& player) {
    this->name = player.name;
    this->orderList = player.orderList;
    this->hand = player.hand;
    this->orderList = player.orderList;
    this->territories = player.territories;
    this->eliminated = player.eliminated;
    this->reinforcementPool = player.reinforcementPool;
}

Player& Player::operator=(const Player& player) {
	this->name = player.name;
	this->orderList = player.orderList;
	return *this;
}

Player::~Player() {
	this->name.clear();
	delete this->orderList;


    // if the Player is not eliminated when the game is over their Hand has not already been cleared
    if (!this->eliminated)
    {
        // clear the Player's Hand
        Hand* hand = this->getHandOfPlayer(); // for readability
        for (int i = 0; i < this->hand->getCardsOnHand().size(); i++)
        {
            delete hand->getCardsOnHand()[i];
            hand->getCardsOnHand()[i] = nullptr;
        }
        hand->getCardsOnHand().clear(); // Player's Hand size is now 0
        hand = nullptr;

        delete this->hand; // delete Player's Hand pointer
    }

    for (int i = 0; i < this->territories.size(); i++)
    {
        this->territories[i] = nullptr; // avoid dangling pointers
    }
    this->territories.clear(); // remove placeholder memory locations

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
int Player::getPlayerTurnNumber()
{
    return playerNumber;
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

void Player::addTerritory(Territory* t)
{
    this->territories.push_back(t);
    t->setOwner(this);
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
