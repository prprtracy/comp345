#pragma once
/*
* @author: Qichen Liu (40055916)
* @date: 2021/11/11
* @version: 2.0 (part 4)
*/
#include <string>
#include <vector>
#include "Player.h"
#include "Map.h"

using namespace std;

class Territory;
class Player;

class Orders
{
public:
	/*
	* contain one default constructor,
	* one destrucotr to avoid memory leaks
	* one copy constructor
	* implement the '=' operator for deep copy purposes
	* another constructor for create an invalid order
	* overloads stream insertion operator for print out the expect output
	*/
	Orders();
	~Orders();
	Orders(Player*, string);
	Orders(const Orders& order);
	Orders& operator = (const Orders& order);
	/*
	* define the validate, execute as pure virtual method,
	* in order to allowed the subclass of Order can overwirte the functions which have the same function name
	*/
	virtual bool validate() = 0;
	virtual void execute() = 0;
	friend ostream& operator<<(ostream& os, const Orders& orders);
	virtual string get_order();
	Player* get_player();
protected:
	Player* own_player;
private:
	string order_type;
};

class Deploy : public Orders
{
public:
	Deploy();
	~Deploy();
	Deploy(Player*, Territory*, int);
	Deploy(const Deploy& deploy);
	Deploy& operator = (const Deploy& deploy);
	/*
	* each subclass need to overwrite the validate and exectue
	*/
	bool validate() override;
	void execute() override;
	friend ostream& operator<<(ostream& os, const Deploy& deploy);
	string get_order() override;

private:
	string order_type;
	Territory* territory;
	int num_armies;
};

class Advance : public Orders
{
public:
	Advance();
	~Advance();
	Advance(Player*, Territory*, Territory*, int);
	Advance(const Advance& advance);
	Advance& operator = (const Advance& advance);
	/*
	* each subclass need to overwrite the validate and exectue
	*/
	bool validate() override;
	void execute() override;
	friend ostream& operator<<(ostream& os, const Advance& advance);
	string get_order() override;

private:
	string order_type;
	Territory* source_terr;
	Territory* adjacent_terr;
	int num_armies;
};

class BombO : public Orders
{
public:
	BombO();
	~BombO();
	BombO(Player*, Territory*);
	BombO(const BombO& bomb);
	BombO& operator = (const BombO& bomb);
	/*
	* each subclass need to overwrite the validate and exectue
	*/
	bool validate() override;
	void execute() override;
	friend ostream& operator<<(ostream& os, const BombO& bomb);
	string get_order() override;

private:
	string order_type;
	Territory* target;
};

class Blockade : public Orders
{
public:
	Blockade();
	~Blockade();
	Blockade(Player*, Territory*);
	Blockade(const Blockade& blockade);
	Blockade& operator = (const Blockade& blockade);
	/*
	* each subclass need to overwrite the validate and exectue
	*/
	bool validate() override;
	void execute() override;
	friend ostream& operator<<(ostream& os, const Blockade& blockade);
	string get_order() override;

private:
	string order_type;
	Territory* territory;
};

class Airlift : public Orders
{
public:
	Airlift();
	~Airlift();
	Airlift(Player*, Territory*, Territory*, int);
	Airlift(const Airlift& airlift);
	Airlift& operator = (const Airlift& airlift);
	/*
	* each subclass need to overwrite the validate and exectue
	*/
	bool validate() override;
	void execute() override;
	friend ostream& operator<<(ostream& os, const Airlift& airlift);
	string get_order() override;

private:
	string order_type;
	Territory* source_terr;
	Territory* target_terr;
	int num_armies;
};

class Negotiate : public Orders
{
public:
	Negotiate();
	~Negotiate();
	Negotiate(Player*, Player*);
	Negotiate(const Negotiate& negotiate);
	Negotiate& operator = (const Negotiate& negotiate);
	/*
	* each subclass need to overwrite the validate and exectue methods
	*/
	bool validate() override;
	void execute() override;
	friend ostream& operator<<(ostream& os, const Negotiate& negotiate);
	string get_order() override;

private:
	string order_type;
	Player* target_player;
};

class OrderList
{
public:
	OrderList();
	~OrderList();
	OrderList(const OrderList& order_list);
	OrderList& operator = (const OrderList& orderList);
	void add(Orders* order);
	void move(int old_position, int new_position);// according the index of a order move to a new position
	void remove(int position);// delete a order of the order list
	friend ostream& operator<<(ostream& os, const OrderList& ol);
	Orders* pop(); //get the first order of the list, then execute this order. once the order executed, it will remove from the list
	void print_ol();

    vector<Orders*> order_list;
};

