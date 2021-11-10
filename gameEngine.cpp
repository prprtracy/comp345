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

//==================================Reinforcement Phase==============================
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

//==================================Issuing Orders Phase==============================
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

//==================================Orders Execution Phase==============================
void Engine::executeOrdersPhase(Player* thisPlayer)
{
    // execute deploy orders
    while(thisPlayer->get_orderList()->order_list.size() != 0) {
        thisPlayer->get_orderList()->pop();
    }
}


//==================================Main Game Loop==============================
// Loops through 3 phases
void Engine::mainGameLoop()
{

    Player* winner = nullptr;
    while (winner == nullptr)
    {
        removePlayers(); // remove players that have no territory
        winner = checkWinner(); // check if there is a winner
        if (winner != nullptr)
        {
            break;
        }

        // ===============Reinforcement phase========
        for (int i = 0; i < this->players.size(); i++)
        {
            if (!this->players.at(i)->isLost())
            {
                reinforcementPhase(players.at(i));
            }
        }
        cout << endl;

        // ============Issuing Orders phase============
        for (int i = 0; i < this->players.size(); i++)
        {
            cout << this->players.at(i)->get_name() << endl;
            if (!this->players.at(i)->isLost())
            {
                issueOrdersPhase(this->players.at(i));
            }
        }
        cout << endl;

        //=========== Orders execution phase=================
        for (int i = 0; i < this->players.size(); i++)
        {
            if (!this->players.at(i)->isLost())
            {
                executeOrdersPhase(players.at(i));
            }
        }
        cout << endl;

    }

    cout << "#############   END Game  ###########################" << endl;
    cout << "        Congratulations, " << winner->get_name() << " You won!" << endl;
    cout << "########################################" << endl;
}

//method to remove the player that does not have any country
void Engine::removePlayers()
{
    Player* thisPlayer = nullptr;
    for (int i = 0; i < this->getPlayers().size(); i++)
    {
        thisPlayer = this->players[i];
        // check if a player has no territory and will be removed
        if (thisPlayer->getTerritories().size() <= 0)
        {
            cout << thisPlayer->get_name() << " has lost the game :(" << endl;

            // the players should put back their cards
            Hand* hand = thisPlayer->getHandOfPlayer();
            for (int j = 0; j < hand->getCardsOnHand().size(); j++)
            {
                this->deck->insert(hand->getCardsOnHand()[j]); // put Cards back to the deck
                hand->getCardsOnHand()[j] = nullptr;
            }
            hand->getCardsOnHand().clear(); // Player's Hand size is now 0
            hand = nullptr;
            thisPlayer->setLostPlayer(); // set the player is lost the game
        }
    }
    thisPlayer = nullptr;
}

// Checks if a Player has won the game; if so return that winning Player, else return nullptr
// a Player has won if they conrol all the Territories on the Map
Player* Engine::checkWinner()
{
    int playersNum = 0; // number of players still in the game
    Player* winner = nullptr;
    for (int i = 0; i < this->getPlayers().size(); i++)
    {
        if (!this->getPlayers().at(i)->isLost())
        {
            playersNum++;
            winner = this->getPlayers().at(i);
        }
    }

    if (playersNum == 1) {
        return winner;
    }
    return nullptr;
}













