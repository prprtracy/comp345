#pragma once
#include <string>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

using namespace std;

class Order;
class OrderList;
class Card;
class Hand;

class Player {
private:
	OrderList* orderList;
	string name;
	Hand* hand;
    int reinforcementPool;

public:
	//constructors
	Player();
	Player(string);
	Player(const Player& player);
	//operstor
	Player& operator = (const Player& player);
	//distructor
	~Player();
	void toAttack();
	void toDeffend();
	void issueOrder(string);
	string get_name();
	//print out the address of the player's orderlist
	OrderList* get_orderList();
	//print out the stored orders of the orderlist
	void print_orderList();
	//set the player's hand cards
	void setCardsOnHand(Hand* hand);
	//get the hand cards of the player
	Hand* getHandOfPlayer();

    // territories belonging to the player
    std::vector<Territory*> territories;
    //get all territories belong to the player
    vector<Territory*> getTerritories();


    // Getter and setter for reinforcementPool
    int getReinforcementPool() { return reinforcementPool; };
    void setReinforcementPool(int a) { reinforcementPool = a; };


};
