#pragma once
#include<fstream>
#include"commandProcessor.h"
using namespace std;

class fileCommandProcessorAdaptor {
	public:
	//the file adaptor contains a filename parameter
	string fileName;
	//default constructor
	fileCommandProcessorAdaptor() {
	}
	//parameter constructor
	fileCommandProcessorAdaptor(string s) {
		fileName = s;
	}
	//read method that read each line as a command and store into a string vector
	vector<string> readCommand() {
		vector<string> list;
		string a;
		ifstream file(fileName);
		while (getline(file, a)) {
			list.push_back(a);
		}
		return list;
	}
};