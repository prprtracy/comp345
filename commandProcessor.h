#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <iostream>
#include<vector>
#include<string>
using namespace std;

class command {
public:
    //the command object contains two string parameter, content and effect after execution
    string content;
    string effect;
    command(string s);
    void setContent(string s);
    string getContent();
    void saveEffect(string s);
};

class commandList {
public:
    //the commandList contains just the vector of the commmand
    vector<command> list;
    commandList();
    commandList(vector<command> v);
    void setList(vector<command> v);
    vector<command> getList();
    void add(command c);
};

class Tournament {
public:
    string M;
    string P;
    int G;//number of games
    int D;//number of turns
    Tournament();
    Tournament(string m, string p, int g, int d);
    vector<string> getm(); //return the vecotr of map
    vector<string> getp(); //return the vector of players
    int getg(); //return number of games
    int getd(); //return number of turns
    void showTournament(); //print the details of the game
    void showResult (Tournament t); //print the final result of the game
};

class commandProcessor {
private:
    string readCommand();
    void saveCommand(string s);
public:
    //the commandProcessor contains a command list
    bool isTournament(string s);
    vector<string> cutTournament(string s);
    string makeM(vector<string> v);
    string makeP(vector<string> v);
    int makeG(vector<string> v);
    int makeD(vector<string> v);
    Tournament createTournament(string command);
    commandList lis;
    commandProcessor();
    commandProcessor(commandList cl);
    string cut(string s);
    void getCommand();
    void getFileCommand(vector<string> v);
    void showList();
    bool validate(string state, string s);
    void execute(string state, int i);
};
#endif