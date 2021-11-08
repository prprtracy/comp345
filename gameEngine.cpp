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

    int bonusArmies = 0; // owning whole Continent bonus
    int reinforcement =3; //the min of reinforcement armies is 3

    //check if the player owns the Continent
    Continent* currContinent = nullptr;
    //going through each Continent
    for (int i = 0; i < map->allContinentsInMap.size(); i++)
    {
        currContinent = map->allContinentsInMap[i];
//if the player owns the continent, he/she will get the bonus armies
        if (currContinent->controlsContinent(currPlayer))
            bonusArmies += currContinent->bonusArmies;
    }
    currContinent = nullptr;

    // Player gets number of armies equal to their number of Territories / 3, unless this number is less than 3
    if ((currPlayer->getTerritories().size() / 3) > reinforcement)
        reinforcement = currPlayer->getTerritories().size() / 3;

// add armies to the reinforcement pool
    currPlayer->setReinforcementPool(reinforcement + bonusArmies);

    cout << currPlayer->get_name() << " received " << reinforcement << " new reinforcements "
         << "and " << bonusArmies << " bonus reinforcements." << endl;
    cout << " In total the player has " << currPlayer->getReinforcementPool() << " armies in their reinforcement pool." << endl;
    cout << "\nEnd of Reinforcement Phase" << endl;

}

// Calls the issueOrder method of the player's strategy class
void Engine::issueOrdersPhase(Player* currPlayer) {

    string o;
    cout<<"Issue Order Phase"<<endl;
    cout<<"\nPlease enter your order: Deploy, Advance, Bomb, Blockade, Airlift, Negotiate"<<endl;
    cin >> o;
    currPlayer->issueOrder(o);

}














