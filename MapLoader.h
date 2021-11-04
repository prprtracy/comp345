#pragma once
#include "Map.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class MapLoader {

private:
	string* fileName;
public:
	MapLoader();
	MapLoader(MapLoader& map);
	MapLoader& operator = (const MapLoader& map);
	~MapLoader();

	MapLoader(string fileName);
	Map* ReadMap(string filePath);
	virtual Map* GetMap(std::string filePath);

	vector<string> splitString(string s);

	friend ostream& operator<<(std::ostream& o, const MapLoader& ml); //ostream operator
};

