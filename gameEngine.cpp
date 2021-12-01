#include <iostream>
#include "gameEngine.h"
#include <random>
#include <chrono> 
//#include "Map.h"
//#include "MapLoader.h"
//#include "Player.h"
//#include "Orders.h"
//#include "Cards.h"
//#include "CommandProcessor.h"

Engine::Engine()
{
    this->map = nullptr;
    vector<Player*> players;
    this->firstPlayer = nullptr;
    this->deck = nullptr;
    this->numOfPlayers = 0;
    this->observerOn = false;
    this->phase = "empty";
    this->phaseObserver = nullptr;
    this->gameStatsObserver = nullptr;
}

//GameEngine::GameEngine()
//{
//    this->map = nullptr;
//    vector<Player*> players;
//    this->firstPlayer = nullptr;
//    this->deck = nullptr;
//    this->numOfPlayers = 0;
//    this->observerOn = false;
//    this->phase = "empty";
//    this->phaseObserver = nullptr;
//    this->gameStatsObserver = nullptr;
//}

// Copy constructor. Creates a deep copy of this GameEngine, and all of its components.
// TODO: how to copy first player
Engine::Engine(Engine& game)
{
    this->map = new Map(*game.map);
    this->players;
    for (int i = 0; i < game.players.size(); i++)
    {
        this->players.push_back(new Player(*game.players.at(i)));
    }
    this->firstPlayer = game.firstPlayer;
    this->deck = new Deck(*game.deck);
    this->numOfPlayers = game.numOfPlayers;
    this->observerOn = game.observerOn;
    this->phase = game.phase;
}

// Destructor
// This should be the only destructor called so it deletes all corresponding components (Map, Players, Deck, etc).
Engine::~Engine()
{
    delete this->map;
    delete this->deck;
    this->firstPlayer = nullptr;

    for (int i = 0; i < this->players.size(); i++)
    {
        delete this->players[i];
        this->players.at(i) = nullptr;
    }
    this->players.clear();

    delete this->phaseObserver;
    delete this->gameStatsObserver;
}

//==================================Startup Phase==============================
void Engine::startupPhase()
{
    string order;
    cout << "Welcome!" << endl;
    do {
        cout << "Please one of the orders in the list:" << endl;
        cout << "loadmap" << endl;
        cout << "validatemap" << endl;
        cout << "addplayer" << endl;
        cout << "gamestart" << endl;
        cin >> order;
        if (order == "loadmap")
        {
            loadmap();
        }
        else if(order == "validatemap")
        {
            validateMap();
        }
        else if (order == "addplayer")
        {
            addplayer();
        }
        else if (order == "gamestart")
        {
            gameStart();
        }
    } while (order != "gamestart");

}


//==================================Reinforcement Phase==============================
void Engine::reinforcementPhase(Player* thisPlayer)
{
    phase = "Reinforcement Phase";
    notify();
    cout << "\nConduct Reinforcement Phase" << endl;

    int bonusArmies = 0; // owning whole Continent bonus
    int reinforcement = 3; //the min/default of reinforcement armies are 3

    //check if the player owns the Continent
    Continent* currContinent = nullptr;
    //going through each Continent
    for (int i = 0; i < map->allContinentsInMap.size(); i++)
    {
        currContinent = map->allContinentsInMap[i];
        //if the player owns the continent, he/she will get the bonus armies
        if (currContinent->controlsContinent(thisPlayer))
            bonusArmies += currContinent->bonusArmies;
    }
    currContinent = nullptr;

    // Player gets number of armies equal to their number of Territories / 3, unless this number is less than 3
    if ((thisPlayer->getTerritories().size() / 3) > reinforcement)
        reinforcement = thisPlayer->getTerritories().size() / 3;

    // add armies to the reinforcement pool
    thisPlayer->setReinforcementPool(reinforcement + bonusArmies);

    cout << thisPlayer->get_name() << " received " << reinforcement << " new reinforcements "
         << "and " << bonusArmies << " bonus reinforcements." << endl;
    cout << " In total the player has " << thisPlayer->getReinforcementPool() << " armies in their reinforcement pool." << endl;
    cout << "\nEnd of Reinforcement Phase" << endl;

}

//==================================Issuing Orders Phase==============================
// Calls the issueOrder method of the player's strategy class
void Engine::issueOrdersPhase(Player* thisPlayer) {

    phase = "Issue Order Phase";
    notify();
    string o;
    cout << "Issue Order Phase" << endl;
    //if the player has armies in the pool, ask the player to deploy
    if (thisPlayer->getReinforcementPool() != 0) {
        cout << "Deploy Order" << endl;
        thisPlayer->toDefend();
        thisPlayer->issueOrder("Deploy");
    }
    //if the player has card on hand, ask the player to play the card
    if (thisPlayer->getHandOfPlayer()->getCardsOnHand().size() != 0) {
        cout << "\nPlease play one of your cards: " << endl;
        for (int i = 0; i < thisPlayer->getHandOfPlayer()->getCardsOnHand().size(); i++) {
            cout << thisPlayer->getHandOfPlayer()->getCardsOnHand().at(i) << ' ';
        }
        cin >> o;
        //using the while loop to make sure the user input a correct command
        while (!count(thisPlayer->getHandOfPlayer()->getCardsOnHand().begin(), thisPlayer->getHandOfPlayer()->getCardsOnHand().end(), o)) {
            cout << "\nError! Please re-entre. You have cards: " << endl;
            for (int i = 0; i < thisPlayer->getHandOfPlayer()->getCardsOnHand().size(); i++) {
                cout << thisPlayer->getHandOfPlayer()->getCardsOnHand().at(i) << ' ';
            }
            cin >> o;
        }

    }
    thisPlayer->issueOrder(o);//call the issue order with the user's input

    //everyone should have an advance order
    cout << "\nAdvance Order" << endl;
    thisPlayer->toAttack();
    thisPlayer->toDefend();
    thisPlayer->issueOrder("Advance");
}

//==================================Orders Execution Phase==============================
void Engine::executeOrdersPhase(Player* thisPlayer)
{
    // execute deploy orders
    phase = "Execute Order Phase";
    notify();
    while (thisPlayer->get_orderList()->order_list.size() != 0) {
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

void Engine::loadmap()
{
    string mapName;
    cout << "Please key in the file name!" << endl;
    cin >> mapName;
    map->GetMap(mapName);
    cout << "Map successfully loaded!" << endl;
}

void Engine::validateMap()
{
    bool isValid = false;
    cout << "Please keyin the map file name!" << endl;
    isValid = map->validate();
    if (map != NULL || !isValid)
    {
       cout << "Map has been validated!" << endl;
            
    }
    else
    {
      cout << "Map loading failed! pls try again." << endl;
      loadmap();
    }
    
}

void Engine::addplayer()
{
    string playerName;
    do
    {
        cout << "There should be 2-6 players, pls keyin the next players' name! Type 'Enough' to stop adding." << endl;
        cin >> playerName;
        numOfPlayers++;
        if (playerName == "Enough" && numOfPlayers >= 2)
        {
            break;
        }
        if (playerName == "Enough" && numOfPlayers < 2)
        {
            cout << "Please add at least one more player!";
        }
    } while (numOfPlayers < 2 || numOfPlayers > 5);
}

 void Engine::tournament() {
     int pointer = 0;
     vector<string> engine= {"start","maploaded","map validated","player added","win"};
     //creates the command processor and file adaptor
     commandProcessor cp = commandProcessor();
     fileCommandProcessorAdaptor fcpa = fileCommandProcessorAdaptor("commands.txt");
     //the startup menu provides two options to input the commands
     cout << "beginning command processor test\n";
     cout << "select one of the following input method:\n";
     cout << "1. input by console\n" << "2. input from a .txt file\n";
     int selection = 0;
     cin >> selection;
     //the looping menu stops at execute
     while (selection == 1 || selection == 2||selection==3) {
         //option 1, input by console calling the getcommand method
         if (selection == 1) {
             cout << "Please enter the command:\n";
             cp.getCommand();
             cout << "\nCurrent commands(first in first out):\n";
             cp.showList();
             cout << "Please select one of the following choices:\n";
             cout << "1. continue input by console.\n" << "2. input by a .txt file\n" << "3. end of input and start execute\n";
             cin >> selection;
         }
         //option 2, input by file input stream calling the getfilecommand method
         if (selection == 2) {
             cout << "reading file " << fcpa.fileName << "...\n";
             cp.getFileCommand(fcpa.readCommand());
             cout << "\nCurrent commands(first in first out):\n";
             cp.showList();
             cout << "Please select one of the following choices:\n";
             cout << "1. continue input by console.\n" << "2. input by a .txt file\n" << "3. end of input and start execute\n";
             cin >> selection;
         }
         //option 3 and looping, validating and excuting the methods from the list
         if (selection == 3) {
             int index = 0;
             cout << "start executing the command list\n";
             cout << "simulated game engine start looping\n";
             while (pointer < 5&&index<cp.lis.getList().size()) {
                 cout << "current phase: " << engine[pointer]<<"\n";
                 cp.execute(engine[pointer],index);
                 string s = cp.lis.list[index].getContent();
                 if (s.compare("loadmap") == 0)
                     pointer = 1;
                 if (s.compare("map loaded") == 0)
                     pointer = 1;
                 if (s.compare("validemap") == 0)
                     pointer = 2;
                 if (s.compare("addplayer") == 0)
                     pointer = 2;
                 if (s.compare("gamestart") == 0)
                     pointer = 3;
                 if (s.compare("replay") == 0)
                     pointer = 0;
                 if (s.compare("quit") == 0)
                     pointer = 5;
             }
             cout << "execution finished, thanks for using";
         }
     }
 }

void Engine::gameStart()

    int turn = 0;
    int numOfArmies;
    this->deck = new Deck();
    Player* p = nullptr;
    vector<Territory*> territoriesCopy = map->listOfTerritories;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(territoriesCopy.begin(), territoriesCopy.end(), std::default_random_engine(seed));
    shuffle(players.begin(), players.end(), std::default_random_engine(seed));

    //distribute the territories
    for (int i = 0; i < territoriesCopy.size(); i++)
    {
        territoriesCopy[i]->setOwner(players[turn]); // set the owner of this Territory to be the Player it is assigned to
        players[turn]->addTerritory(territoriesCopy[i]);
        turn++;

        if (turn > (players.size() - 1))
            turn = 0;
    }
    //set players' gaming order
    std::cout << "The playing order is: ";
    for (int i = 0; i < numOfPlayers; i++)
    {
        cout << players[i]->getPlayerNumber() << " ";
    }
    cout << endl;

    //attach number to all players
    for (int i = 0; i < players.size(); i++)
    {
        players.at(i)->addReinforcements(numOfArmies);
    }
    for (int i = 0; i < numOfPlayers; i++) {
        for (int i = 0; i < 10; i++)
        {
            this->deck->draw(p);
        }
        this->players.push_back(p);
    }
    
}

//method to remove the player that does not have any country (lost the game)
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