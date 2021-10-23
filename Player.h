#pragma once
#include <string>
#include <vector>
#include "Orders.h"

using namespace std;

class Order;
class OrderList;

class Player {
private:
	OrderList* orderList;
	string name;

public:
	//constructors
	Player();
	Player(string);
	Player(const Player & player);
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
};
