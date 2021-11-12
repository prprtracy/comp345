#include <iostream>
#include "Orders.h"

using namespace std;

Orders::Orders()
{
    order_type = "anOrder";
    this->own_player = nullptr;
}

Orders::~Orders()
{
}

Orders::Orders(Player* player, string str)
{
    this->own_player = player;
    order_type = str;
}

Orders::Orders(const Orders& order) {
    this->own_player = order.own_player;
    this->order_type = order.order_type;
}

Orders& Orders::operator=(const Orders& order) {
    this->own_player = order.own_player;
    this->order_type = order.order_type;
    return *this;
}

string Orders::get_order() {
    return this->order_type;
}

Player* Orders::get_player() {
    return this->own_player;
}

ostream& operator<<(ostream& os, const Orders& order) {
    return os << order.order_type << endl;
}

//Deploy implementation
Deploy::Deploy()
{
    order_type = "Deploy";
}

Deploy::Deploy(Player* player, Territory* territory, int num_armies)
{
    order_type = "Deploy";
    this->territory = territory;
    this->num_armies = num_armies;
}

Deploy::Deploy(const Deploy& deploy) {

    this->order_type = deploy.order_type;
    this->territory = deploy.territory;
    this->num_armies = deploy.num_armies;
}

Deploy& Deploy::operator=(const Deploy& deploy) {
    this->order_type = deploy.order_type;
    this->territory = deploy.territory;
    this->num_armies = deploy.num_armies;
    return *this;
}

Deploy::~Deploy()
{
}

bool Deploy::validate() {
    if (territory->getOwner() == get_player()) {
        cout << "This deploy order is valid." << endl;
        return true;
    }
    cout << "Invalid deploy order." << endl;
    return false;
}

void Deploy::execute() {
    if (validate()) {
        cout << "This deploy order is valid and prepare to execute." << endl;
        this->own_player->decreaseReinforcementPool(num_armies);
        this->territory->addArmies(num_armies);
    }
    else {
        cout << "Error: deploy execute method cannot execute." << endl;
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

Advance::Advance(Player* player, Territory* source, Territory* target, int armies) {
    order_type = "Advance";
    this->source_terr = source;
    this->adjacent_terr = target;
    this->num_armies = armies;
}

Advance::Advance(const Advance& advance) {
    this->order_type = advance.order_type;
    this->source_terr = advance.source_terr;
    this->adjacent_terr = advance.adjacent_terr;
    this->num_armies = advance.num_armies;
}

Advance& Advance::operator=(const Advance& advance) {
    this->order_type = advance.order_type;
    this->source_terr = advance.source_terr;
    this->adjacent_terr = advance.adjacent_terr;
    this->num_armies = advance.num_armies;
    return *this;
}

Advance::~Advance()
{
}

bool Advance::validate() {
    if (source_terr->getOwner() == own_player && source_terr->isAdjacent(adjacent_terr->_id)) {
        cout << "This advance order is valid." << endl;
        return true;
    }
    cout << "Invalid advance order." << endl;
    return false;
}

void Advance::execute() {
    if (validate()) {
        cout << "This Advance order is valid and prepare to execute." << endl;
        if (source_terr->getOwner() == own_player && adjacent_terr->getOwner() == own_player) {
            source_terr->removeArmies(num_armies);
            adjacent_terr->addArmies(num_armies);
        }
        else {
            if (adjacent_terr->armyNum > 0) {

            }
        }
    }
    else {
        cout << "Error: this advance method cannot execute." << endl;
    }
}

string Advance::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const Advance& advance) {
    return os << advance.order_type << endl;
}

//Bomb implementation
BombO::BombO()
{
    order_type = "Bomb";
}

BombO::BombO(Player* player, Territory* territory) {
    order_type = "Bomb";
    this->target = territory;
}

BombO::BombO(const BombO& bomb) {
    this->order_type = bomb.order_type;
    this->target = bomb.target;
}

BombO& BombO::operator=(const BombO& bomb) {
    this->order_type = bomb.order_type;
    this->target = bomb.target;
    return *this;
}

BombO::~BombO()
{
}

bool BombO::validate() {
    bool checkAdjacent = false;
    for (int i = 0; i < own_player->getTerritories().size(); i++) {
        if (own_player->getTerritories().at(i)->isAdjacent(target->_id)) {
            checkAdjacent = true;
        }
    }
    if (target->getOwner() != own_player && checkAdjacent) {
        cout << "This bomb order is valid." << endl;
        return true;
    }
    else {
        cout << "Invalid bomb order." << endl;
        return false;
    }
}

void BombO::execute() {
    if (validate()) {
        cout << "This Bomb order is valid and prepare to execute." << endl;
        target->removeArmies(target->armyNum / 2);
    }
    else {
        cout << "Error: this bomb order cannot execute." << endl;
    }
}

string BombO::get_order() {
    return this->order_type;
}

ostream& operator<<(ostream& os, const BombO& bomb) {
    return os << bomb.order_type << endl;
}

//Blockade implementation
Blockade::Blockade()
{
    order_type = "Blockade";
}

Blockade::Blockade(Player* player, Territory* target) {
    order_type = "Blockade";
    this->territory = target;
}

Blockade::Blockade(const Blockade& blockade) {
    this->order_type = blockade.order_type;
    this->territory = blockade.territory;
}

Blockade& Blockade::operator=(const Blockade& blockade) {
    this->order_type = blockade.order_type;
    this->territory = blockade.territory;
    return *this;
}

Blockade::~Blockade()
{
}

bool Blockade::validate() {
    if (territory->getOwner() == own_player) {
        cout << "This blockade order is valid." << endl;
        return true;
    }
    cout << "Invalid blockade order." << endl;
    return false;
}

void Blockade::execute() {
    if (validate()) {
        cout << "This Blockade order is valid and prepare to execute." << endl;
        territory->addArmies(territory->armyNum);
        territory->setOwner(new Player());
    }
    else {
        cout << "Error: this blockade method cannot execute." << endl;
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

Airlift::Airlift(Player* player, Territory* source, Territory* target, int armies) {
    order_type = "Airlift";
    this->source_terr = source;
    this->target_terr = target;
    this->num_armies = armies;
}

Airlift::Airlift(const Airlift& airlift) {
    this->order_type = airlift.order_type;
    this->source_terr = airlift.source_terr;
    this->target_terr = airlift.target_terr;
    this->num_armies = airlift.num_armies;
}

Airlift& Airlift::operator=(const Airlift& airlift) {
    this->order_type = airlift.order_type;
    this->source_terr = airlift.source_terr;
    this->target_terr = airlift.target_terr;
    this->num_armies = airlift.num_armies;
    return *this;
}

Airlift::~Airlift()
{
}

bool Airlift::validate() {
    if (source_terr->getOwner() == own_player && target_terr->getOwner() == own_player) {
        cout << "This airlift order is valid." << endl;
        return true;
    }
    cout << "Invalid airlift order." << endl;
    return false;
}

void Airlift::execute() {
    if (validate()) {
        cout << "This Airlift order is valid and prepare to execute." << endl;
        source_terr->removeArmies(num_armies);
        target_terr->addArmies(num_armies);
    }
    else {
        cout << "Error: This airlift order cannot execute." << endl;
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

Negotiate::Negotiate(Player* player1, Player* player2) {
    order_type = "Negotiate";
    this->target_player = player2;
}

Negotiate::Negotiate(const Negotiate& negotiate) {
    this->order_type = negotiate.order_type;
    this->target_player = negotiate.target_player;
}

Negotiate& Negotiate::operator=(const Negotiate& Negotiate) {
    this->order_type = Negotiate.order_type;
    this->target_player = Negotiate.target_player;
    return *this;
}

Negotiate::~Negotiate()
{
}

bool Negotiate::validate() {
    if (own_player != target_player) {
        cout << "This negotiate order is valid." << endl;
        return true;
    }
    cout << "Invalid negotiate order." << endl;
    return false;
}

void Negotiate::execute() {
    if (validate()) {
        cout << "This Negotiate order is valid and prepare to execute." << endl;
    }
    else {
        cout << "Error: This negotiate order cannot execute." << endl;
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

OrderList::OrderList(const OrderList& ol) {
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
        os << i + 1 << " " << curr << endl;
        os << i + 1 << " " << curr->get_order() << endl;

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
