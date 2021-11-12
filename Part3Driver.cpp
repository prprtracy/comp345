//
// Created by Zhangbin Cai on 2021-11-10.
//
#include <iostream>
#include <string>
#include "Map.h"
#include "Player.h"
#include "GameEngine.h"


MapLoader* Load() {
        MapLoader* mapLoader = new MapLoader();
        return mapLoader;
    }

int main(){

    string filePath;
    bool isValid = false;

     Map* map=nullptr;

    do {
        cout << "Please select a map: ";
        cin >> filePath;
        MapLoader *mapLoader = Load();
        map = mapLoader->GetMap(filePath);
        map->validate();
    }
    while (map == NULL || !isValid );
    Engine gameEngine;

    gameEngine.setNbrOfPlayers();


//	gameEngine.startupPhase();

	//assign territories
	vector<Territory*> territoryList = map->allTerritoriesInMap;
	for (int i = 0; i < territoryList.size(); i++)
	{
		cout << territoryList[i]->get_name() + " belongs to Player " << territoryList[i]->getOwner() << endl;
	}

	vector<Player*> playerList = gameEngine.getPlayers();

	cout << "\nEvery player will start with " << gameEngine.getInitialArmy() << " armies." << endl;

	cout << "Player " << playerList[0]->getPosition() << " has " << playerList[0]->getReinforcementPool() << " armies in their reinforcement pool." << endl;

	cout << "\n====================================== MAIN GAME LOOP =========================================" << endl;
	gameEngine.mainGameLoop();

	delete map;
	map = nullptr;

    return 0;
}
