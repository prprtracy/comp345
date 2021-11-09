#pragma once
/*
* @author: Qichen Liu (40055916)
* @date: 2021/10/08
* @version: 1.0 (part 3)
*/
#include <string>
#include <vector>

using namespace std;

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
	Orders(string);
	Orders(const Orders& order);
	Orders& operator = (const Orders& order);
	/*
	* define the validate, execute as virtual function,
	* in order to allowed the subclass of Order can overwirte the functions which have the same function name
	*/
	virtual bool validate();
	virtual void execute();
	friend ostream& operator<<(ostream& os, const Orders& orders);
	virtual string get_order();
private:
	string order_type;
};

class Deploy : public Orders
{
public:
	Deploy();
	~Deploy();
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
};

class Advance : public Orders
{
public:
	Advance();
	~Advance();
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
};

class BombO : public Orders
{
public:
	BombO();
	~BombO();
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
};

class Blockade : public Orders
{
public:
	Blockade();
	~Blockade();
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
};

class Airlift : public Orders
{
public:
	Airlift();
	~Airlift();
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
};

class Negotiate : public Orders
{
public:
	Negotiate();
	~Negotiate();
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

