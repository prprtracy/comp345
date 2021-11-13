#pragma once
#include<fstream>
#include"commandProcessor.h"
using namespace std;

class fileCommandProcessorAdaptor {
	public:
	
	string fileName;
	commandList lis;

	fileCommandProcessorAdaptor() {
	}

	fileCommandProcessorAdaptor(string s) {
		fileName = s;
	}

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