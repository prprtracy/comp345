#include"commandProcessor.h"
using namespace std;
    //The methods of the command object.
    //parameter constructor
    command::command(string s) {
        content = s;
    }
    //regular setter&getter
    void command::setContent(string s) {
        content = s;
    }
    string command::getContent() {
        return content;
    }
    //save effect method, use to edit the effect parameter in command object
    void command::saveEffect(string s) {
        effect = s;
    }
    //The methods of the commandList object that serve as the collection of the commands.
    //default constructor
    commandList::commandList() {
    }
    //parameter constructor
    commandList::commandList(vector<command> v) {
        list = v;
    }
    //setter&getter
    void commandList::setList(vector<command> v) {
        list = v;
    }

    vector<command> commandList::getList() {
        return list;
    }
    //the method to push the command objects into the list
    void commandList::add(command c) {
        list.push_back(c);
    }
    //The methods of the commandProcessor object
    //readcommand method that take and validate the string from the input of the console, in invalid case it will return blank space and output warning message
    string commandProcessor::readCommand() {
        string a;
        cin >> a;
        string b = cut(a);
        if (b.compare("loadmap") == 0 || b.compare("validatemap") == 0 || b.compare("addplayer") == 0 || b.compare("gamestart") == 0 || b.compare("replay") == 0 || b.compare("quit") == 0)
            return a;
        else {
            cout << a << " is not a valid command.\n";
            return " ";
        }
    }
    // savecommand method that takes the string, generate the command and save it into the list object inside the commandProcessor
    void commandProcessor::saveCommand(string s) {
        if (s.compare(" ") != 0) {
            command c = command(s);
            lis.add(c);
        }
    }
    //default constructor
    commandProcessor::commandProcessor() {
    }
    //parameter constructor
    commandProcessor::commandProcessor(commandList cl) {
        lis = cl;
    }
    //the method to help analyze the command phrase such and loadmap<> and addplayer<> that contains a <> bracket, it find and cutout the bracket and return the substring without the bracket.
    string commandProcessor::cut(string s) {
        string t;
        int i = s.find("<");
        int j = s.find(">");
        if (i != -1) {
            if (j != -1) {
                t = s.substr(0, i);
                return t;
            }
            else
                return s;
        }
        else
            return s;
    }
    //the public method that call both the read and save methods
    void commandProcessor::getCommand() {
        string s = readCommand();
        saveCommand(s);
        cout << "done.\n";
    }
    //the saving method of the file input, takes a list of string and push them into the list by a for loop
    void commandProcessor::getFileCommand(vector<string> v) {
        for (int i = 0; i < v.size(); i++) {
            string b = cut(v[i]);
            if (b.compare("loadmap") == 0 || b.compare("validatemap") == 0 || b.compare("addplayer") == 0 || b.compare("gamestart") == 0 || b.compare("replay") == 0 || b.compare("quit") == 0)
                saveCommand(v[i]);
        }
        cout << "done.\n";
    }
    //the show list method to demonstrate current commands in the list.
    void commandProcessor::showList() {
        for (int i = 0; i < lis.getList().size(); i++) {
            cout << lis.list[i].getContent()<<"\n";
        }
    }

    //the validate method, that take the current state and match with the command, then return a bool that whether or not its valid
    bool commandProcessor::validate(string state, string s) {
        string t = cut(s);
        int u = 0; 
        if (t.compare("loadmap") == 0) {
            if (state.compare("start") == 0 || state.compare("maploaded") == 0)
                return true;
        }
        if (t.compare("validatemap") == 0) {
            if (state.compare("maploaded") == 0)
                return true;
        }
        if (t.compare("addplayer") == 0) {
            if (state.compare("mapvalidated") == 0 || state.compare("playersadded") == 0)
                return true;
        }
        if (t.compare("gamestart") == 0) {
            if (state.compare("playersadded") == 0)
                return true;
        }
        if (t.compare("replay") == 0) {
            if (state.compare("win") == 0)
                return true;
        }
        if (t.compare("quit") == 0) {
            if (state.compare("win") == 0)
                return true;
        }
            return false;
    }
    //the execute method that generates and save the effect of command, also output the message
    void commandProcessor::execute(string state,int i) {
        string s = lis.list[i].getContent();
        string t = cut(s);

        if (t.compare("listofmapfiles") == 0) {
            int j = s.find("<");
            int k = s.find(">");
            string u = s.substr(j , k-1);
            lis.list[i].saveEffect("list of maps"+u);
            cout << "map Map1, Map2, Map3 loaded.\n";
        }



        if (t.compare("listofplayerstrategies") == 0) {
            int j = s.find("<");
            int k = s.find(">");
            string u = s.substr(j , k-1);
            lis.list[i].saveEffect("list of players trategies"+u);
            cout << "trategies including Aggressive, Benevolent, Neutral, Cheater.\n";
        }

        if (t.compare("numberofgames") == 0) {
            int j = s.find("<");
            int k = s.find(">");
            string u = s.substr(j , k-1);
            lis.list[i].saveEffect("numberofgames"+u);
            cout << "number of games:" <<u "\n";
        }

        if (t.compare("maxnumberofturns") == 0) {
            int j = s.find("<");
            int k = s.find(">");
            string u = s.substr(j , k-1);
            lis.list[i].saveEffect("maxnumberofturns"+u);
            cout << "max number of turns:" <<u "\n";
        }

            if (t.compare("loadmap") == 0) {
                int j = s.find("<");
                int k = s.find(">");
                string u = s.substr(j , k-1);
                lis.list[i].saveEffect("loaded map"+u);
                cout << "map " << u << " loaded.\n";
            }
            if (t.compare("validatemap") == 0) {
                lis.list[i].saveEffect("map validated");
                cout << "map validated.\n";
            }
            if (t.compare("addplayer") == 0) {
                int j = s.find("<");
                int k = s.find(">");
                string u = s.substr(j, k-1);
                lis.list[i].saveEffect("player " + u + " added");
                cout << "player " << u << " added.\n";
            }
            if (t.compare("gamestart") == 0) {
                lis.list[i].saveEffect("game started");
                cout << "all set, game begin.\n";
            }
            if (t.compare("replay") == 0) {
                lis.list[i].saveEffect("restarted");
                cout << "restarting the game.\n";
            }
            if (t.compare("quit") == 0) {
                lis.list[i].saveEffect("quit the game");
                cout << "game finished, shutting down.\n";
            }
    }