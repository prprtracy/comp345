#include"commandProcessor.h"
using namespace std;

    command::command(string s) {
        content = s;
    }
    void command::setContent(string s) {
        content = s;
    }
    string command::getContent() {
        return content;
    }

    void command::saveEffect(string s) {
        effect = s;
    }

    commandList::commandList() {
    }

    commandList::commandList(vector<command> v) {
        list = v;
    }

    void commandList::setList(vector<command> v) {
        list = v;
    }

    vector<command> commandList::getList() {
        return list;
    }

    void commandList::add(command c) {
        list.push_back(c);
    }

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

    void commandProcessor::saveCommand(string s) {
        if (s.compare(" ") != 0) {
            command c = command(s);
            lis.add(c);
        }
    }

    commandProcessor::commandProcessor() {
    }

    commandProcessor::commandProcessor(commandList cl) {
        lis = cl;
    }

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

    void commandProcessor::getCommand() {
        string s = readCommand();
        saveCommand(s);
        cout << "done.\n";
    }

    void commandProcessor::getFileCommand(vector<string> v) {
        for (int i = 0; i < v.size(); i++) {
            string b = cut(v[i]);
            if (b.compare("loadmap") == 0 || b.compare("validatemap") == 0 || b.compare("addplayer") == 0 || b.compare("gamestart") == 0 || b.compare("replay") == 0 || b.compare("quit") == 0)
                saveCommand(v[i]);
        }
        cout << "done.\n";
    }

    bool commandProcessor::validate(string state, command c) {
        string s = c.getContent();
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

    bool commandProcessor::execute(string state,int i) {
        string s = lis.list[i].getContent();
        string t = cut(s);
        if (validate(state, lis.list[i])) {
            if (t.compare("loadmap") == 0) {
                int i = s.find("<");
                int j = s.find(">");
                string u = s.substr(i + 1, j);
                lis.list[i].saveEffect("loaded map " + u);
                cout << "map " << u << " loaded.\n";
                return true;
            }
            if (t.compare("validatemap") == 0) {
                lis.list[i].saveEffect("map validated");
                cout << "map validated.\n";
                return true;
            }
            if (t.compare("addplayer") == 0) {
                int i = s.find("<");
                int j = s.find(">");
                string u = s.substr(i + 1, j);
                lis.list[i].saveEffect("player " + u + " added");
                cout << "player " << u << " added.\n";
                return true;
            }
            if (t.compare("gamestart") == 0) {
                lis.list[i].saveEffect("game started");
                cout << "all set, game begin.\n";
                return true;
            }
            if (t.compare("replay") == 0) {
                lis.list[i].saveEffect("restarted");
                cout << "restarting the game.\n";
                return true;
            }
            if (t.compare("quit") == 0) {
                lis.list[i].saveEffect("quit the game");
                cout << "game finished, shutting down.\n";
                return true;
            }
        }
        else
            return false;
    }