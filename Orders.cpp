#include <iostream>
#include "Orders.h"

using namespace std;

Orders::Orders()
{
    order_type = "anOrder";
}

Orders::~Orders()
{
}

Orders::Orders(string str)
{
    order_type = str;
}

Orders::Orders(const Orders & order) {
    this->order_type = order.order_type;
}

Orders& Orders::operator=(const Orders& order) {
    this->order_type = order.order_type;
    return *this;
}

//the following two method leave for implementing in a2
bool Orders::validate() {
    cout << "This is the validate method for verify if the order is valid." << endl;
    return false;
}

void Orders::execute() {
    if (validate()) {
        cout << "This order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order..." << endl;
    }
}

string Orders::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Orders& order) {
    return os << order.order_type << endl;
}

//Deploy implementation
Deploy::Deploy()
{
    order_type = "Deploy";
}

Deploy::Deploy(const Deploy & deploy) {

    this->order_type = deploy.order_type;
}

Deploy& Deploy::operator=(const Deploy& deploy) {
    this->order_type = deploy.order_type;
    return *this;
}

Deploy::~Deploy()
{
}

bool Deploy::validate() {
    cout << "This is the validate method for verify the deploy order." << endl;
    return true;
}

void Deploy::execute() {
    if (validate()) {
        cout << "This deploy order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order...(D)" << endl;
    }
}

string Deploy::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Deploy& deploy) {
    return os << deploy.order_type << endl;
}

//Advance implementation
Advance::Advance()
{
    order_type = "Advance";
}


Advance::Advance(const Advance & advance) {
    this->order_type = advance.order_type;
}

Advance& Advance::operator=(const Advance& advance) {
    this->order_type = advance.order_type;
    return *this;
}

Advance::~Advance()
{
}

bool Advance::validate() {
    cout << "This is the validate method for verify the Advance order." << endl;
    return true;
}

void Advance::execute() {
    if (validate()) {
        cout << "This Advance order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order...(A)" << endl;
    }
}

string Advance::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Advance& advance) {
    return os << advance.order_type << endl;
}

//Bomb implementation
Bomb::Bomb()
{
    order_type = "Bomb";
}


Bomb::Bomb(const Bomb & bomb) {
    this->order_type = bomb.order_type;
}

Bomb& Bomb::operator=(const Bomb& bomb) {
    this->order_type = bomb.order_type;
    return *this;
}

Bomb::~Bomb()
{
}

bool Bomb::validate() {
    cout << "This is the validate method for verify the Bomb order." << endl;
    return true;
}

void Bomb::execute() {
    if (validate()) {
        cout << "This Bomb order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order...(B)" << endl;
    }
}

string Bomb::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Bomb& bomb) {
    return os << bomb.order_type << endl;
}

//Blockade implementation
Blockade::Blockade()
{
    order_type = "Blockade";
}


Blockade::Blockade(const Blockade & blockade) {
    this->order_type = blockade.order_type;
}

Blockade& Blockade::operator=(const Blockade& blockade) {
    this->order_type = blockade.order_type;
    return *this;
}

Blockade::~Blockade()
{
}

bool Blockade::validate() {
    cout << "This is the validate method for verify the Blockade order." << endl;
    return true;
}

void Blockade::execute() {
    if (validate()) {
        cout << "This Blockade order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order...(BL)" << endl;
    }
}

string Blockade::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Blockade& blockade) {
    return os << blockade.order_type << endl;
}

//Airlift implementation
Airlift::Airlift()
{
    order_type = "Airlift";
}

Airlift::Airlift(const Airlift & airlift) {
    this->order_type = airlift.order_type;
}

Airlift& Airlift::operator=(const Airlift& airlift) {
    this->order_type = airlift.order_type;
    return *this;
}

Airlift::~Airlift()
{
}

bool Airlift::validate() {
    cout << "This is the validate method for verify the Airlift order." << endl;
    return true;
}

void Airlift::execute() {
    if (validate()) {
        cout << "This Airlift order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order...(AI)" << endl;
    }
}

string Airlift::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Airlift& airlift) {
    return os << airlift.order_type << endl;
}

//Negotiate implementation
Negotiate::Negotiate()
{
    order_type = "Negotiate";
}

Negotiate::Negotiate(const Negotiate & negotiate) {
    this->order_type = negotiate.order_type;
}

Negotiate& Negotiate::operator=(const Negotiate& Negotiate) {
    this->order_type = Negotiate.order_type;
    return *this;
}

Negotiate::~Negotiate()
{
}

bool Negotiate::validate() {
    cout << "This is the validate method for verify the Negotiate order." << endl;
    return true;
}

void Negotiate::execute() {
    if (validate()) {
        cout << "This Negotiate order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Sorry, this is an invalid order...(N)" << endl;
    }
}

string Negotiate::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Negotiate& negotiate) {
    return os << negotiate.order_type << endl;
}

//order list implement
OrderList::OrderList()
{
    vector<Orders*> ol;
    this->order_list = ol;
}

OrderList::~OrderList()
{
    //delete every element in the vector
    for (int i = 0; i < this->order_list.size(); i++) {
        delete this->order_list[i];
    }
    //clear this vector, release the memory
    this->order_list.clear();
}

OrderList::OrderList(const OrderList & ol) {
    order_list = ol.order_list;
}

OrderList& OrderList::operator=(const OrderList& orderList) {
    if (&orderList != this) {
        this->order_list = orderList.order_list;
    }
    return *this;
}

// add a new order to the end of the order list
void OrderList::add(Orders* order) {
    order_list.push_back(order);
}

void OrderList::move(int old_position, int new_position) {
    //check if the move requirement is valid
    if (old_position < 0 || old_position > order_list.size()) {
        cout << "Error: invalid position" << endl;
        return;
    }
    /*Check if the desired new position is out of bounds, and if the given new_position is out of bounds,
    it is automatically moved to the first position in the list.*/
    int valid_new_position = (new_position < 0 || new_position > order_list.size()) ? 0 : new_position;
    Orders* elem_ptr = order_list[old_position];
    order_list.erase(order_list.begin() + old_position);
    order_list.insert(order_list.begin() + valid_new_position, elem_ptr);
}

void OrderList::remove(int position) {
    //check if the move requirement is valid
    if (position < 0 || position > order_list.size()) {
        cout << "invalid position" << endl;
        return;
    }
    order_list.erase(order_list.begin() + position);
}


ostream& operator<<(ostream& os, const OrderList& ol) {
    os << "Order list:" << endl;
    for (int i = 0; i < ol.order_list.size(); i++) {
        Orders* curr = ol.order_list.at(i);
        os << i+1 << " " << curr << endl;
        os << i+1 << " " << curr->get_order() << endl;
        
    }
    return os;
}

Orders* OrderList::pop() {
    Orders* od_ptr = order_list.at(0);
    order_list.erase(order_list.begin());
    return od_ptr;

}

void OrderList::print_ol() {
    Orders* curr;
    int i = 0;
    for (vector<Orders*>::iterator it = order_list.begin(); it < order_list.end(); ++it) {
        curr = *it;
        i++;
        cout << "order" << i << " " << (*it)->get_order() << endl;
    }
}
