#include "Map.h"
#include <string>
#include <map>
#include <algorithm>


//==================================Map=======================================
/* Constructors */
//  Default Constructor
Map::Map()
{
	name = "";
}
//Constructor
Map::Map(string name)
{
	name = name;
}
// Copy Constructor
Map::Map(const Map &map)
{
	name = map.name;
    allContinentsInMap = map.allContinentsInMap;
}

// Assignment operator
Map& Map::operator = (const Map &map)
{
	if (&map != this)
	{
		name = map.name;
        allContinentsInMap = map.allContinentsInMap;
        allTerritoriesInMap = map.allTerritoriesInMap;
	}
	return *this;
}
// destructor
Map::~Map()
{
	for (int i = 0; i < this->allContinentsInMap.size(); i++)
	{
		delete this->allContinentsInMap[i];
		this->allContinentsInMap[i] = nullptr;
	}
	this->allContinentsInMap.clear();

	for (int i = 0; i < this->allTerritoriesInMap.size(); i++)
	{
		this->allTerritoriesInMap[i] = nullptr;
	}
	this->allTerritoriesInMap.clear();
}

/* Accessors & Mutators */
vector<Territory *> Map::get_territories() {
    return allTerritoriesInMap;
}

vector<Continent *> Map::get_continents() {
    return allContinentsInMap;
}

/*
* Add a continent to allContinentsInMap vector
*/
void Map::addContinentToMap(Continent* continent)
{
	allContinentsInMap.push_back(continent);
}

/*
* Add a territory to allTerritoriesInConti vector
*/
void Map::addTerritoryToMap(Territory* territory)
{
	allTerritoriesInMap.push_back(territory);
}


//if false, map is invalid, if true, check all continent and country are connected to each other
//if false, map is invalid, if true, map is valid
//DFS
// Check if territorries, and continents are connected
//=========================================
bool Map::validate()
{
	bool isConnTerr = true;
	bool isConnCont = true;
    bool tIsUnique = false;
    tIsUnique= verifyUniqueContinents();
	bool* travelledTerritories = new bool[allTerritoriesInMap.size()] {false };
	bool* travelledContinents = new bool[allContinentsInMap.size()]{false };

    verifyConnectedMap(allTerritoriesInMap.at(0), travelledTerritories, travelledContinents);

	for (int i = 0; i < allTerritoriesInMap.size(); i++)
	{
		if (!travelledTerritories[i])
            isConnTerr = false;
	}
	// Check if continents are connected
	for (int i = 0; i < allContinentsInMap.size(); i++)
	{
		if (!travelledContinents[i])
            isConnCont = false;
	}
	delete[] travelledTerritories;
	delete[] travelledContinents;

	if (isConnTerr && isConnCont && tIsUnique){
        cout<<"Valid map! Have Fun"<<endl;
        return true;
    }

	else{
        cout<<"Invalid map, please make sure you enter a valid file"<<endl;
        return false;
    }

}

/*
* DFS method to traverse the node to check if they are connected
*/
void Map::verifyConnectedMap(Territory* current, bool visitedTerritories[], bool visitedContinents[])
{
	if (!visitedTerritories[current->_id - 1])
	{
		visitedTerritories[current->_id - 1] = true;
		if (current->continentID != NULL && !visitedContinents[current->continentID - 1])
		{

			visitedContinents[current->continentID - 1] = true;
		}
		for (Territory* neighbor : allTerritoriesInMap.at(current->_id - 1)->allAdjTerritories)
		{
            //recursiverly call the function
            verifyConnectedMap(neighbor, visitedTerritories, visitedContinents);
		}
	}
}


 // Verify if each territory belongs to only one continent
bool Map::verifyUniqueContinents()  {

    map <string, string> territory_continent;

    for (Continent* continent: allContinentsInMap) {
        for (Territory* territory: continent->get_territories()) {

            if(territory_continent.count(territory->get_name()) != 0) {
                return false;
            }
            territory_continent[territory->get_name()] = continent->get_name();
        }
    }
    return true;
}


//*
//* print out the detailed info of the map
//*/
//ostream& operator << (ostream &out, const Map &map)
//{
//	out << "List of Continents and their Countries" << endl;
//	out << endl;
//	for (int i = 0; i < map.allContinentsInMap.size(); i++)
//	{
//		out << map.allContinentsInMap.at(i)->_id << " " << map.allContinentsInMap.at(i)->name << endl;
//
//		for (int j = 0; j < map.allContinentsInMap.at(i)->allTerritoriesInConti.size(); j++)
//		{
//			out << "   " << j + 1 << ". " << map.allContinentsInMap.at(i)->allTerritoriesInConti.at(j)->_id << " " <<
//                map.allContinentsInMap.at(i)->allTerritoriesInConti.at(j)->name << endl;
//		}
//		out << endl;
//	}
//
//	return out;
//}

//========================================Continent=======================================
/* Constructors */
//  Default Constructor
Continent::Continent()
{
    _id = 0;
	name = "";
	int bonusArmies = 0;
}

/*
* Constructor
*/
Continent::Continent(int id, string contName, int bonusArmies)
{
    _id = id;
	name = contName;

}
//  Copy Constructor
Continent::Continent(const Continent &continent)
{
    _id = continent._id;
	name = continent.name;
    bonusArmies = continent.bonusArmies;
    allAdjContinents = continent.allAdjContinents;
    allTerritoriesInConti = continent.allTerritoriesInConti;
}

// Assignment operator
Continent& Continent::operator = (const Continent &continent)
{
	if (&continent != this)
	{
        _id = continent._id;
		name = continent.name;
        bonusArmies = continent.bonusArmies;
        allAdjContinents = continent.allAdjContinents;
        allTerritoriesInConti = continent.allTerritoriesInConti;
	}
	return *this;
}

// destructor
Continent::~Continent()
{
	for (int i = 0; i < this->allTerritoriesInConti.size(); i++)
	{
		delete this->allTerritoriesInConti[i];
		this->allTerritoriesInConti[i] = nullptr;
	}
	this->allTerritoriesInConti.clear();

	for (int i = 0; i < this->allAdjContinents.size(); i++)
	{
		this->allAdjContinents[i] = nullptr;
	}
	this->allAdjContinents.clear();
}

//print the continent info
ostream& operator << (ostream &out, const Continent &c)
{
	cout << endl;
	out << "The continent - " << c.name << endl;
	out << endl;

	out << "List of Territories of '" << c.name << "' (_id, name)" << endl;
	out << endl;
	for (int i = 0; i < c.allTerritoriesInConti.size(); i++)
	{
		out << i + 1 << ". " << c.allTerritoriesInConti.at(i)->_id << " " << c.allTerritoriesInConti.at(i)->name << endl;
	}
	out << endl;
	out << endl;
	return out;
}
/* Accessors & Mutators */
string Continent::get_name() const {
    return name;
}

int Continent::get_army_bonus() const
{
    return bonusArmies;
}

vector<Territory *> Continent::get_territories() const {
    return allTerritoriesInConti;
}
/*
* Adds a territory to a continent
*/
void Continent::addTerritoryToContinent(Territory * territory)
{
	allTerritoriesInConti.push_back(territory);
}

/*
* Prints all allTerritoriesInConti of a continent
*/
void Continent::printTerritories()
{
	cout << "Continents and their countries: '" << this->name << "'" << endl;
	for (int i = 0; i < this->allTerritoriesInConti.size(); i++)
	{
		cout << i + 1 << ". " << this->allTerritoriesInConti.at(i)->_id << " " << this->allTerritoriesInConti.at(i)->name << endl;
	}
	cout << endl;
}


Continent* Map::getContinentByID(int id)
{
	return allContinentsInMap[id - 1];
}

Continent * Map::getContinentByName(string name)
{
	for (int i = 0; i < allContinentsInMap.size(); i++)
	{
		if (allContinentsInMap.at(i)->name == name)
			return allContinentsInMap.at(i);
	}
	return NULL;
}

/*
* Returns a territory object
*/
Territory* Map::getTerritoryByID(int id)
{
	return allTerritoriesInMap[id - 1];
}

Territory * Map::getTerritoryByName(string name)
{
	for (int i = 0; i < allTerritoriesInMap.size(); i++)
	{
		if (allTerritoriesInMap.at(i)->name == name)
			return allTerritoriesInMap.at(i);
	}
	return NULL;
}

// Checks if the input Player owns all Territories of this Continent. Returns true if yes, otherwise returns false.
// used in GameEngine::reinforcementPhase()
bool Continent::controlsContinent(Player* player)
{
    for (int i = 0; i < this->allTerritoriesInConti.size(); i++)
    {
        if (this->allTerritoriesInConti[i]->owner != player)
            return false;
    }
    return true;
}

//=============================================Territory================================================
//  Default Constructor
Territory::Territory()
{
    _id = 0;
	name = "";
    continentID = 0;
    armyNum = 0;
	this->owner = nullptr;
}

// Constructor
Territory::Territory(int idT, string nameT, int continentId)
{
    _id = idT;
	name = nameT;
    continentID = continentId;
    armyNum = 10;
	this->owner = nullptr;
}

//  Copy Constructor
Territory::Territory(const Territory &territory)
{
    _id = territory._id;
	name = territory.name;
//    allAdjTerritories = territory.allAdjTerritories;
    continentID = territory.continentID;
    armyNum = territory.armyNum;
	this->owner = territory.owner;
}

// Assignment operator
Territory& Territory::operator = (const Territory &territory)
{
	if (&territory != this)
	{
        _id = territory._id;
		name = territory.name;
        allAdjTerritories = territory.allAdjTerritories;
        armyNum = territory.armyNum;
	}
	return *this;
}

// Destructor
Territory::~Territory()
{
	this->owner = nullptr;
	for (int i = 0; i < this->allAdjTerritories.size(); i++)
	{
		this->allAdjTerritories[i] = nullptr;
	}
	this->allAdjTerritories.clear();
}

/* Accessors & Mutators */
string Territory::get_name() const {
    return name;
}

int Territory::get_id() const {
    return _id;
}

int Territory::get_continent_id() const {
    return continentID;
}
/*
* Get territory by id
*/
Territory* Continent::getTerritoryByID(int id)
{
	for (int i = 0; i < allTerritoriesInConti.size(); i++)
	{
		if (allTerritoriesInConti[i]->_id == id)
			return allTerritoriesInConti[i];
	}

	return nullptr;
}

/*
* Get the owner of the territory
*/
Player* Territory::getOwner()
{
	return this->owner;
}

bool Territory::isAdjacent(int terr_id) {
	for (int i = 0; i < allAdjTerritories.size(); i++) {
		if (allAdjTerritories.at(i)->_id == terr_id) {
			return true;
		}
	}
	return false;
}

/*
* connect two neighbour territories
*/
void Map::connectTwoTerritory(Territory * t1, Territory * t2)
{
    t1->allAdjTerritories.push_back(t2);
}

void Map::printConnectedTerritory(Territory* territory)
{
    cout << "Territories connected to " << territory->name << ": " << endl;
    for (int i = 0; i < territory->allAdjTerritories.size(); i++)
    {
        cout << territory->allAdjTerritories.at(i)->name << "; ";
    }
}

bool Territory::haveTerritory(vector<Territory*> territories)
{
    if (territories.size() != 0)
    {
        for (int i = 0; i < territories.size(); i++)
        {
            if (territories.at(i) == this)
                return true;
        }
    }
    return false;
}

bool Territory::addArmies(int n)
{
    if (n > 0)
    {
        armyNum += n;
        return true;
    }
    return false;
}

bool Territory::removeArmies(int n)
{
    if (n > 0)
    {
        armyNum -= n;
        return true;
    }
    return false;
}