//
// Created by Zhangbin Cai on 2021-11-10.
//
#include <iostream>
#include <string>
#include "Map.h"
#include "Player.h"
#include "GameEngine.h"
int main(){

    Engine gameEngine;


    //Testing Map Select."
	gameEngine.readMap();
    vector<Player*> playerList = gameEngine.getPlayerList();

	cout << "\nEvery player will start with " << gameEngine.getInitialArmy() << " armies." << endl;

	cout << "Player " << playerList[0]->getPosition() << " has " << playerList[0]->getReinforcementPool() << " armies in their reinforcement pool." << endl;

	cout << "\n====================================== MAIN GAME LOOP =========================================" << endl;
	Engine.mainGameLoop();

	delete map;
	map = nullptr;

    return 0;
}
