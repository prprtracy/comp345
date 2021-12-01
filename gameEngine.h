#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "GameObserver.h"
#include "commandProcessor.h"
using namespace std;

class Engine
{
public:
	Engine();
	Engine(Engine& game);
	~Engine();
	void start();
	void startupPhase();
	Map* GetMap();
	Deck* getDeck();
	void mainGame();
	vector<Player*> getPlayers();
	string phaseStage();
	string command;

    void tournament();
	//set the main loop and phases
	void mainGameLoop();
	void loadmap();

	void validateMap();
	void addplayer();
	void gameStart();
	void reinforcementPhase(Player* thisPlayer); // void for now
	void issueOrdersPhase(Player* thisPlayer);
	void executeOrdersPhase(Player* thisPlayer);

	Player* checkWinner();

private:
	Map* map;
	vector<Player*> players;
	Player* firstPlayer;
	Deck* deck;
	int numOfPlayers;
	bool observerOn;
	string phase;

	PhaseObserver* phaseObserver;
	GameStatisticsObserver* gameStatsObserver;
	
	void selectMap();
	void createComponents();
	void setObservers();
	void setInitialArmies();
	void setRandomOrder();
	void setRandomTerritory();
	void removePlayers(); // checks if a Player has lost the game
	void endGamePhase(Player* winner); // launches end game winner message

	GameEngine& operator =(const GameEngine& game);
	friend ostream& operator <<(ostream& strm, GameEngine& game);
	
};