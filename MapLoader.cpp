#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

//Default Constructor
MapLoader::MapLoader() {
	this->fileName = nullptr;
}

//Copy Constructorc
MapLoader::MapLoader(MapLoader &map){
    fileName = map.fileName;
}

//Assignment operator
MapLoader& MapLoader:: operator = (const MapLoader &map) {
	return *this;
}

//Destructor
MapLoader::~MapLoader() {
	delete fileName;
}

// constructor
MapLoader::MapLoader(string fileName) {
	this->fileName = new std::string(fileName);
}

//get map
Map* MapLoader::GetMap(string filePath) {
	return ReadMap(filePath);
}

//split the line using istringstream
vector<string> MapLoader::splitString(string s)
{
    // Used to split string around spaces.
    istringstream ss(s);
    vector<string> v;
    while (ss >> s)
    {
        v.push_back(s);
    }
    return v;
}


//read a map
Map* MapLoader::ReadMap(string filePath) {
	try {
		Map* map = new Map();
		Continent* continent;
		Territory* territory;
		string line = "";
		bool hasContinent = false;
		bool hasCountries = false;
		bool hasBorders = false;

		ifstream mapReader;
		mapReader.open(filePath);

		if (!mapReader) {
			cout << "Invalid file" << endl;
			return nullptr;
		}
		else {
			while (getline(mapReader, line))
			{
				//Reads continents
				if (line.find("[continents]") == 0) {
					getline(mapReader, line);

					int continentID = 1;
//                    cout << "Continents: "<< endl;
					while (line.find("[countries]") != 0) {
						if (line == "")
							break;
						vector<string> elements = splitString(line);
                        continent = new Continent(continentID, elements[0], stoi(elements[1]));
                        map->addContinentToMap(continent);
						continentID++;
//						cout  << line << endl;
						getline(mapReader, line);
					}
					hasContinent = true;
				}

				if (line.find("[countries]") == 0 && hasContinent) {
					getline(mapReader, line);
//                    cout << "Countries:"<< endl;
					while (line.find("[borders]") != 0) {
						if (line == "")
							break;

						//add allTerritoriesInConti
						vector<string> elements = splitString(line);
                        territory = new Territory(stoi(elements[0]), elements[1], stoi(elements[2]));
                        map->allContinentsInMap[stoi(elements[2]) - 1]->addTerritoryToContinent(territory);
                        map->addTerritoryToMap(territory);

//						cout  << line << endl;
						getline(mapReader, line);
					}

					hasCountries = true;
				}
              //read border
				if (line.find("[borders]") == 0 && hasContinent && hasCountries) {
					getline(mapReader, line);
//                    cout << "Border: "<< endl;
                    while (!line.empty()) {
						if (line == "")
							break;
						vector<string> closeTerr = splitString(line);
						Territory* t1 = map->getTerritoryByID(stoi(closeTerr[0]));
						for (int i = 1; i < closeTerr.size(); i++)
						{
							Territory* t2 = map->getTerritoryByID(stoi(closeTerr[i]));
                            map->connectTwoTerritory(t1, t2);
						}
//						cout  << line << endl;
						getline(mapReader, line);
					}
					hasBorders = true;
				}
			}

			if (hasContinent && hasCountries && hasBorders) {

				mapReader.close();
				return map;

			}
			else {
				cout << "Invalid File" << endl;
				mapReader.close();
				return nullptr;
			}
        }
//        validate();
    }
	catch (const std::exception& e) {
		return nullptr;

	}
}



