#pragma once
#include "Map.h"
//#include "Player.h"
#include <iostream>
#include <vector>


using namespace std; 

/**
* Zhangbin Cai
* 40165425
*
*/

class Player;

//-------------------------------------------Territory------------------------------
class Territory
{
public:
    int _id;
    int continentID;
    int armyNum;
    string name;
    Player* owner;
    vector<Territory*> allAdjTerritories;

    /* constructors */
	Territory(); // Default Constructor
	Territory(int id, string name, int continentId);//Constructor
	Territory(const Territory &territory); // Copy Constructor
	~Territory(); // Destructor
    Territory& operator = (const Territory& territory); // Assignment operator

    /* Accessors and Mutators */
    int get_continent_id() const;
    int get_id() const;
    string get_name() const;
    int get_armies() const;
    Player* getOwner();
    void setOwner(Player* player);// set the owner of this Territory
    bool haveTerritory(vector<Territory*> territories); // checks if this Territory is contained in the input vector

    friend bool operator ==(const Territory& t1, const Territory& t2);
    friend ostream & operator << (ostream &out, const Territory &c);
};

//-----------------------------------Continent--------------------------
class Continent
{
public:
    int _id;
    int bonusArmies;//bonus armies in this continent
    string name;
    vector<Territory*> allTerritoriesInConti;
    vector<Continent*> allAdjContinents;

    /* constructors */
	Continent(); // Default Constructor
	Continent(int id, string contName, int bonusArmies);//Constructor
	Continent(const Continent &continent); // Copy Constructor
	~Continent();//destructor
    Continent& operator = (const Continent& continent); // Assignment operator

    /* Accessors and Mutators */
    string get_name() const;
    int get_army_bonus() const;
    vector<Territory*> get_territories() const;
	void addTerritoryToContinent(Territory* territory);
	void printTerritories();
	Territory* getTerritoryByID(int id);
    friend ostream & operator << (ostream &out, const Continent &c);

    bool controlsContinent(Player* player); // checks if the input Player owns the entire Continent

};
//-----------------------------------------Map-----------------------------
class Map
{
public:
    string name;
    vector<Continent*> allContinentsInMap;
    vector<Territory*> allTerritoriesInMap;

    Map();// Default Constructor
    Map(string name);//Constructor
    Map(const Map &map);//Copy Constructor
    ~Map();//destructor
    Map& operator = (const Map& map); // Assignment operator
   friend ostream & operator << (ostream &out, const Map &m);

    void addContinentToMap(Continent* continent);
    void addTerritoryToMap(Territory* territory);
    void connectTwoTerritory(Territory* t1, Territory* t2);

    /* Accessors and Mutators */
    vector<Territory*> get_territories();
    vector<Continent*> get_continents();
    Continent* getContinentByID(int id);
    Continent* getContinentByName(string name);
    Territory* getTerritoryByID(int id);
    Territory* getTerritoryByName(string name);

    void printConnectedTerritory(Territory* territory);
    bool validate(); // validate the map
    void verifyConnectedMap(Territory* current, bool visitedTerritories[], bool visitedContinents[]);
    bool verifyUniqueContinents();

};














