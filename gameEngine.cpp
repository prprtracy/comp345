#include <iostream>
#include "gameEngine.h"
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"

Engine::Engine() {
	step = State::Start;
	player = new Player();
	orders = new OrderList();
	deck = new Deck();
	playersNum = 1;
}

void Engine::readMap() {
	// if( load successfully)
		cout << "Map has been loaded successfully!";
		setState(State :: mapLoading);
	//else 
		cout << "Map loading failed plz recheck the map!";
		setState(State:: Start);
}

void Engine::mapValidate() {
	// if ( successfully)
	cout << "Map validate successfully!";
	setState(State::addPlayer);
	//else 
	cout << "Map is invalid!";
	setState(State::mapLoading);
}

void Engine::addPlayer() {
	// if( successfully)
	cout << "Player add successfully!";
	setState(State::reinAssign);
}

void Engine::reinAssign() {
	// if( successfully)
	cout << "Reinforcement Assign successfully!";
	setState(State::issueOrder);
	//else
	cout << "Reinforcement Assign failed because of"; // no enough soliders?, etc
}

void Engine::issueOrder() {
	//Users input the order, and process, run, or repeat, etc.
	setState(State::issueOrder);
}

void Engine::endIssueOrder() {
	//Cases close and ruin constructors
	setState(State::exeOrder);
}

void Engine::exeOrder() {
	//make the order effects, ex: bomb card
	//if(win)
	setState(State::win);
	//else
	setState(State::issueOrder);
}

void Engine::endExeOrder() {
	//Cases close and ruin constructors
}

void Engine::reinforcementPhase(Player* currPlayer)
{
    cout << "\nConduct Reinforcement Phase" << endl;
    const int MINIMUM_NUM_ARMIES = 3; // the minimal number of reinforcement armies per turn for any player is 3
    int bonusArmies = 0; // if Player gets bonus reinforcements from owning whole Continent

    Continent* currContinent = nullptr; // for readability

    for (int i = 0; i < map->allContinentsInMap.size(); i++)
    {
        currContinent = map->allContinentsInMap[i];

        if (currContinent->controlsContinent(currPlayer))
            bonusArmies += currContinent->armyvalue;
    }
    currContinent = nullptr;

    // Player gets number of armies equal to their number of Territories / 3, unless this number is less than 3
    if ((currPlayer->getTerritories().size() / 3) > newArmies)
        newArmies = currPlayer->getTerritories().size() / 3;

    cout << "Player " << currPlayer->getPlayerNumber() << " will receive " << newArmies << " new reinforcements "
         << "and " << bonusArmies << " bonus reinforcements." << endl;
    currPlayer->addReinforcements(newArmies + bonusArmies); // add armies
}



