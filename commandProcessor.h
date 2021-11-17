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

class commandProcessor {
private:
	string readCommand();
	void saveCommand(string s);
public:
	//the commandProcessor contains a command list
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