#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <iostream>
#include<vector>
#include<string>
using namespace std;

class command {
public:
	string content;
	string effect;
	command(string s);
	void setContent(string s);
	string getContent();
	void saveEffect(string s);
};

class commandList {
public:
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
	commandList lis;
	commandProcessor();
	commandProcessor(commandList cl);
	string cut(string s);
	void getCommand();
	void getFileCommand(vector<string> v);
	bool validate(string state, command c);
	bool execute(string state, int i);
};
#endif