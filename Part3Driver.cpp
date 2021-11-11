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

	cout << "\nHere are the settings of the Game Engine.\nNumber of Players: " << gameEngine.getNbrOfPlayers() << endl;
	cout << "Map name: ";
	cout<< gameEngine.getMapName() << endl;


	//Testing startup phase
	cout << "\nTesting startup Phase." << endl;
	gameEngine.startupPhase();

	//Territory Assignment
	Map* map = gameEngine.getMap();
	vector<Territory*> territoryList = map->getTerritoryList();
	for (int i = 0; i < territoryList.size(); i++)
	{
		cout << territoryList[i]->getName() + " belongs to Player " << territoryList[i]->getPlayer() << endl;
	}

	vector<Player*> playerList = gameEngine.getPlayerList();
	cout << "\nEvery player will start with " << gameEngine.getInitialArmy() << " armies." << endl;

	cout << "Player " << playerList[0]->getPosition() << " has " << playerList[0]->getReinforcementPool() << " armies in their reinforcement pool." << endl;

	cout << "\n====================================== MAIN GAME LOOP =========================================" << endl;
	gameEngine.mainGameLoop();

	delete map;
	map = nullptr;

    return 0;
}
