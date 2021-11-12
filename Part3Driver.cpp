//
// Created by Zhangbin Cai on 2021-11-10.
//
#include <iostream>
#include <string>
#include "Map.h"
#include "Player.h"
#include "GameEngine.h"
#include <random>
#include <algorithm>
#include <chrono>


MapLoader* Load() {
        MapLoader* mapLoader = new MapLoader();
        return mapLoader;
    }

int main(){

    //select map
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
   //create players
    Player *p1 = new Player("p1");
    Player *p2 = new Player("p2");
    Player *p3 = new Player("p3");
    Player *p4 = new Player("p4");

    vector<Player*> playerList;
    playerList.push_back(p1);
    playerList.push_back(p2);
    playerList.push_back(p3);
    playerList.push_back(p4);

    //Randomizing player order
    srand(unsigned(time(0)));
    vector<int> playerOrder;
    for (int i = 1; i <= 4; i++)
    {
        playerOrder.push_back(i);
    }
    random_shuffle(playerOrder.begin(), playerOrder.end());


    //assign 50 armies to each player in the ReinforcementPool
    for (int i =0; i< playerList.size(); i++){
        playerList[i]->setReinforcementPool(50);
    }


	//assign territories
    vector<Territory*> territoryList = map->get_territories();
//    vector<Territory*> territoriesCopy = map->listOfTerritories;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(territoryList.begin(), territoryList.end(), std::default_random_engine(seed));

    int turn = 0;
    for (int i = 0; i < territoryList.size(); i++)
    {
        territoryList[i]->setOwner(playerList[turn]); // set the owner of this Territory to be the Player it is assigned to
        playerList[turn]->addTerritory(territoryList[i]);
        turn++;

        if (turn > (playerList.size() - 1))
            turn = 0;
    }


	for (int i = 0; i < territoryList.size(); i++)
	{
		cout << territoryList[i]->get_name() + " belongs to Player " << territoryList[i]->getOwner() << endl;
	}



	cout << "\nEvery player will start with " << gameEngine.getInitialArmy() << " armies." << endl;

	cout << "Player " << playerList[0]->getPosition() << " has " << playerList[0]->getReinforcementPool() << " armies in their reinforcement pool." << endl;

	cout << "\n====================================== MAIN GAME LOOP =========================================" << endl;
	gameEngine.mainGameLoop();

	delete map;
	map = nullptr;

    return 0;
}
