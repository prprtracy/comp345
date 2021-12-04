#include"commandProcessor.h"
using namespace std;
//The methods of the command object.
//parameter constructor
command::command(string s) {
    content = s;
}
//regular setter&getter
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

int findAll(string str, string sub) {
    vector<int> positions;
    int pos = str.find(sub, 0);
    while (pos != string::npos)
    {
        positions.push_back(pos);
        pos = str.find(sub, pos + 1);
    }
    return positions.size();
}

void Tournament:: showResult (Tournament t){
    for (int i =1; i <= t.getm().size(); i++){
        cout<<"Map: "<< i <<endl;
        for (int j=1; j<= t.getg(); j++){
            cout<<"Game: "<< j ;
            string random = t.getp()[rand() % t.getp().size()];
            cout<<" Winner: " <<random <<endl;
        }
    }
}

Tournament::Tournament() {}
Tournament::Tournament(string m, string p, int g, int d) {
    M = m;
    P = p;
    G = g;
    D = d;
}

vector<string> Tournament::getm() {
    string s = M;
    vector<string> v;
    int i = s.find(",");
    int j = findAll(s, ",");
    for (int k = 0; k < j; k++) {
        string t = s.substr(0, i);
        v.push_back(t);
        s = s.substr(i + 1);
    }
    v.push_back(s);
    return v;
}

vector<string> Tournament::getp() {
    string s = P;
    vector<string> v;
    int i = s.find(",");
    int j = findAll(s, ",");
    for (int k = 0; k < j; k++) {
        string t = s.substr(0, i);
        v.push_back(t);
        s = s.substr(i + 1);
    }
    v.push_back(s);
    return v;
}


int Tournament::getg() {
    return G;
}

int Tournament::getd() {
    return D;
}

void Tournament::showTournament() {
    cout << "M: " << M;
    cout << "\nP: " << P;
    cout << "\nG: " << G;
    cout << "\nD: " << D;
}

bool commandProcessor::isTournament(string s) {
    string t = s.substr(0, 10);
    if (t.compare("tournament") == 0)
        return true;
    else
        return false;
}

vector<string> commandProcessor::cutTournament(string s) {
    vector<string>v;
    string t = s.substr(10);
    if (t[0] == '-' && t[1] == 'M') {
        int i = t.find(">");
        if (i != -1) {
            string u = t.substr(0, i + 1);
            v.push_back(u);
            t = t.substr(i + 1);
        }
    }
    if (t[0] == '-' && t[1] == 'P') {
        int i = t.find(">");
        if (i != -1) {
            string u = t.substr(0, i + 1);
            v.push_back(u);
            t = t.substr(i + 1);
        }
    }
    if (t[0] == '-' && t[1] == 'G') {
        int i = t.find(">");
        if (i != -1) {
            string u = t.substr(0, i + 1);
            v.push_back(u);
            t = t.substr(i + 1);
        }
    }
    if (t[0] == '-' && t[1] == 'D') {
        int i = t.find(">");
        if (i != -1) {
            string u = t.substr(0, i + 1);
            v.push_back(u);
        }
    }
    return v;
}

string commandProcessor::makeM(vector<string> v) {
    string s = v[0];
    int i = findAll(s, ",");
    if (i >= 1 && i <= 5) {
        int j = s.find("<");
        int k = s.find(">");
        if (j != -1 && k != -1) {
            string t = s.substr(j + 1, k - j - 1);
            return t;
        }
        else
            throw;
    }
    else
        throw;
}

string commandProcessor::makeP(vector<string> v) {
    string s = v[1];
    int i = findAll(s, ",");
    if (i >= 2 && i <= 4) {
        int j = s.find("<");
        int k = s.find(">");
        if (j != -1 && k != -1) {
            string t = s.substr(j + 1, k - j - 1);
            return t;
        }
        else
            throw;
    }
    else
        throw;
}

int commandProcessor::makeG(vector<string> v) {
    string s = v[2];
    int j = s.find("<");
    int k = s.find(">");
    if (j != -1 && k != -1) {
        string t = s.substr(j + 1, k - j);
        int i = stoi(t);
        if (i >= 1 && i <= 5)
            return i;
        else
            throw;
    }
    else
        throw;
}

int commandProcessor::makeD(vector<string> v) {
    string s = v[3];
    int j = s.find("<");
    int k = s.find(">");
    if (j != -1 && k != -1) {
        string t = s.substr(j + 1, k - j);
        int i = stoi(t);
        if (i >= 10 && i <= 50)
            return i;
        else
            throw;
    }
    else
        throw;
}

Tournament commandProcessor::createTournament(string command) {
    try {
        if (isTournament(command)) {
            vector<string> v = cutTournament(command);
            string m = makeM(v);
            string p = makeP(v);
            int g = makeG(v);
            int d = makeD(v);
            Tournament t = Tournament(m, p, g, d);
            return t;
        }
        else
            throw;
    }
    catch (exception e) {
        cout << command << " is not a valid command.\n";
    }
    return Tournament();
}

//The methods of the commandProcessor object
//readcommand method that take and validate the string from the input of the console, in invalid case it will return blank space and output warning message
string commandProcessor::readCommand() {
    string a;
    cin >> a;
    if (isTournament(a))
        return a;
    else {
        string b = cut(a);
        if (b.compare("loadmap") == 0 || b.compare("validatemap") == 0 || b.compare("addplayer") == 0 || b.compare("gamestart") == 0 || b.compare("replay") == 0 || b.compare("quit") == 0)
            return a;
        else {
            cout << a << " is not a valid command.\n";
            return " ";
        }
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
        cout << lis.list[i].getContent() << "\n";
    }
}

//the validate method, that take the current state and match with the command, then return a bool that whether or not its valid
bool commandProcessor::validate(string state, string s) {
    string t;
    if (isTournament(s))
        t = "tournament";
    else
        t = cut(s);
    int u = 0;
    if (t.compare("tournament") == 0) {
        if (state.compare("start") == 0)
            return true;
    }
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
void commandProcessor::execute(string state, int i) {
    string s = lis.list[i].getContent();
    string t = cut(s);
    if (t.compare("loadmap") == 0) {
        int j = s.find("<");
        int k = s.find(">");
        string u = s.substr(j, k - 1);
        lis.list[i].saveEffect("loaded map" + u);
        cout << "map " << u << " loaded.\n";
    }
    if (t.compare("validatemap") == 0) {
        lis.list[i].saveEffect("map validated");
        cout << "map validated.\n";
    }
    if (t.compare("addplayer") == 0) {
        int j = s.find("<");
        int k = s.find(">");
        string u = s.substr(j, k - 1);
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