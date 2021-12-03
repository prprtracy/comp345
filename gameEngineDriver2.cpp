//#include <iostream>
//#include <string>
//
//#include "MapLoader.h"
//#include "Map.h"
//#include "Player.h"
//#include "Cards.h"
//#include "Order.h"
//#include "GameEngine.h"
//#include "PlayerStrategies.h"
//
//void gameEngineDriver2();
//
//int main()
//{
//	gameEngineDriver2();
//
//	Engine* g = new Engine();
//	g->startupPhase();
//	g->mainGameLoop();
//
//	return 0;
//}
//
//void gameEngineDriver2()
//{
//	Engine g;
//
//	cout << "Starting driver for Part 2" << endl;
//	cout << "--------------------------" << endl;
//	g.startupPhase();
//	cout << "Check that territories have been assigned one and only one player: " << endl << endl;
//	Map* m = g.GetMap();
//	for (int i = 0; i < m->listOfTerritories.size(); i++)
//	{
//		cout << "The owner of Territory '" << m->listOfTerritories[i]->name << "' is Player " << m->listOfTerritories[i]->owner->getPlayerNumber() << endl;
//	}
//
//	cout << endl;
//	cout << "Check that players are given an inital number of armies" << endl << endl;
//	vector<Player*> players = g.getPlayers();
//	for (int i = 0; i < players.size(); i++)
//	{
//		cout << "The number of initial armies in the reinforcement pool is " << players[i]->getReinforcementPool() << endl;
//	}
//}