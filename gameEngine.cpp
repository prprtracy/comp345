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
    int reinforcement =3; //the min/default of reinforcement armies are 3

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
    //if the player has armies in the pool, ask the player to deploy
    if (currPlayer->getReinforcementPool() !=0){
        cout<<"Deploy Order"<<endl;
        currPlayer->toDefend();
        currPlayer->issueOrder("Deploy");
    }
    //if the player has card on hand, ask the player to play the card
    if (currPlayer->getHandOfPlayer()->getCardsOnHand().size()!= 0){
        cout<<"\nPlease play one of your cards: "<<endl;
        for(int i=0; i < currPlayer->getHandOfPlayer()->getCardsOnHand().size(); i++){
            cout << currPlayer->getHandOfPlayer()->getCardsOnHand().at(i) << ' ';
        }
        cin >> o;
        //using the while loop to make sure the user input a correct command
        while(!count(currPlayer->getHandOfPlayer()->getCardsOnHand().begin(), currPlayer->getHandOfPlayer()->getCardsOnHand().end(), o)){
            cout<< "\nError! Please re-entre. You have cards: " <<endl;
            for(int i=0; i < currPlayer->getHandOfPlayer()->getCardsOnHand().size(); i++){
                cout << currPlayer->getHandOfPlayer()->getCardsOnHand().at(i) << ' ';
            }
            cin >> o;
        }

    }
    currPlayer->issueOrder(o);//call the issue order with the user's input

    //everyone should have an advance order
    cout<<"\nAdvance Order"<<endl;
    currPlayer->toAttack();
    currPlayer->toDefend();
    currPlayer->issueOrder("Advance");
}

void Engine::executeOrdersPhase(Player* currPlayer)
{
    // execute deploy orders
    while(currPlayer->get_orderList()->order_list.size() != 0) {
        currPlayer->get_orderList()->pop();
    }
}




// Loops through 3 phases
void Engine::mainGameLoop()
{

    Player* winner = nullptr;
    while (winner == nullptr)
    {
        kickPlayers(); // check if a Player owns no Territories; if yes, kick them from the game
        winner = checkWinner(); // check if a Player has won the game
        if (winner != nullptr)
        {
            break;
        }

        // Reinforcement phase
        for (int i = 0; i < this->players.size(); i++)
        {
            if (!this->players.at(i)->isEliminated())
            {
                reinforcementPhase(players.at(i));
            }
        }
        cout << endl;

        // Issuing Orders phase
        for (int i = 0; i < this->players.size(); i++)
        {
            cout << *this->players.at(i) << endl;
            if (!this->players.at(i)->isEliminated())
            {
                issueOrdersPhase(this->players.at(i));
            }
        }
        cout << endl;

        // Orders execution phase
        for (int i = 0; i < this->players.size(); i++)
        {
            if (!this->players.at(i)->isEliminated())
            {
                executeOrdersPhase(players.at(i));
            }
        }
        cout << endl;

    }

    cout << "########################################" << endl;
    cout << "Congratulations, " << winner->get_name() << " You won!" << endl;
    cout << "########################################" << endl;
}

void Engine::kickPlayers()
{
    Player* currPlayer = nullptr; // for readability
    for (int i = 0; i < this->getPlayers().size(); i++)
    {
        currPlayer = this->players[i];
        if (currPlayer->getTerritories().size() <= 0) // if Player has no Territories kick them from the game
        {
            cout << "Player " << currPlayer->getPlayerNumber() << " controls no more Territories. They are removed from the game." << endl;

            // put the losing Player's Cards back in the Deck
            Hand* hand = currPlayer->getHand(); // for readability
            for (int j = 0; j < hand->getCardsInHand().size(); j++)
            {
                this->deck->insertBackToDeck(hand->getCardsInHand()[j]); // put each Card back in the Deck
                hand->getCardsInHand()[j] = nullptr;
            }
            hand->getCardsInHand().clear(); // Player's Hand size is now 0
            hand = nullptr;
            currPlayer->eliminatePlayer(); // sets isEliminated to true
        }
    }
    currPlayer = nullptr;
}















