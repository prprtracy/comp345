#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"

// Haocen Cai, 40089640
//Part V: Game Engine

//States during the engine running
enum class State {
	Start,
	mapLoading,
	mapValidate,
	addPlayer,
	reinAssign,
	issueOrder,
	exeOrder,
	win
};

//Main class
class Engine {

// pointers
private:
	State step;
	Player* player;
	Orders* orders;
	Deck* deck;
	int playersNum;
    Map* map;

    vector<Player*> players;

public:
	Engine();

	//States to define
	string stateToString() {
		switch (step) {
		case State::Start:
			return "Start";
		case State::mapLoading:
			return "mapLoading";
		case State::mapValidate:
			return "mapValidate";
		case State::addPlayer:
			return "addPlayer";
		case State::reinAssign:
			return "reinAssign";
		case State::issueOrder:
			return "issueOrder";
		case State::exeOrder:
			return "exeOrder";
		case State::win:
			return "win";
		}
	}

	//Get and set State
	State getState() {
		return step;
	}

	void setState(State nextStep)
	{
		step = nextStep;
	}

    void setNumberOfPlayers();


    //getters
    int getNumberOfPlayers();
    Map* getMap();

    vector<Player*> getPlayers();

	// all the states method
	void readMap();
	void mapValidate();
	void addPlayer();
	void countryAssign();
	void reinAssign();
	void issueOrder();
	void endIssueOrder();
	void exeOrder();
	void endExeOrder();
	void win();



    //set the main loop and phases
    void mainGameLoop();
    void reinforcementPhase(Player* currPlayer); // void for now
    void issueOrdersPhase(Player* currPlayer);
    void executeOrdersPhase(Player* thisPlayer);
    void removePlayers(); // checks if a Player has lost the game
    Player* checkWinner(); // checks if a Player has won
	void end() {
		exit(0);
	}
};



