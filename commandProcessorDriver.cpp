#include"fileCommandProcessorAdaptor.cpp"
using namespace std;

int main() {
    //simulate engine for demo use, the string in the vector represents each state of the game, the dynamic pointer points to current state
    int pointer = 0;
    vector<string> engine = { "start","maploaded","mapvalidated","playersadded","assignreignforcement","win" };
    //creates the command processor and file adaptor
    commandProcessor cp = commandProcessor();
    fileCommandProcessorAdaptor fcpa = fileCommandProcessorAdaptor("commands.txt");
    //the startup menu provides two options to input the commands
    cout << "beginning command processor test\n";
    cout << "select one of the following input method:\n";
    cout << "1. input by console\n" << "2. input from a .txt file\n";
    int selection = 0;
    cin >> selection;
    //the looping menu stops at execute
    while (selection == 1 || selection == 2 || selection == 3) {
        //option 1, input by console calling the getcommand method
        if (selection == 1) {
            cout << "Please enter the command:\n";
            cp.getCommand();
            int index = cp.lis.list.size()-1;
            if (cp.isTournament(cp.lis.list[index].getContent())) {
                cout << "Entering tournament mode------\n";
                Tournament t = cp.createTournament(cp.lis.list[index].getContent());
                t.showTournament();
                selection = 4;
                t.showResult(t);
            }
            else {
                cout << "\nCurrent commands(first in first out):\n";
                cp.showList();
                cout << "\n";
                cout << "Please select one of the following choices:\n";
                cout << "1. continue input by console.\n" << "2. input by a .txt file\n" << "3. end of input and start execute\n";
                cin >> selection;
            }
        }
        //option 2, input by file input stream calling the getfilecommand method
        if (selection == 2) {
            cout << "reading file " << fcpa.fileName << "...\n";
            cp.getFileCommand(fcpa.readCommand());
            cout << "\nCurrent commands(first in first out):\n";
            cp.showList();
            cout << "\n";
            cout << "Please select one of the following choices:\n";
            cout << "1. input by console.\n" << "2. continue input by another .txt file\n" << "3. end of input and start execute\n";

        }
        //option 3 and looping, validating and excuting the methods from the list
        if (selection == 3) {
            int index = 0;
            cout << "start executing the command list\n";
            cout << "simulated game engine start looping\n";
            while (pointer < engine.size() && index < cp.lis.getList().size()) {
                cout << "current phase: " << engine[pointer] << "\n";
                string s = cp.lis.list[index].getContent();
                string t = cp.cut(s);
                //skipping the ingame event
                if (pointer == 4) {
                    cout << "game running...\ngamefinished.\n";
                    pointer = 5;
                }
                //state modifier in engine
                if (cp.validate(engine[pointer], s)) {
                    cp.execute(engine[pointer], index);
                    if (t.compare("loadmap") == 0)
                        pointer = 1;
                    if (t.compare("validatemap") == 0)
                        pointer = 2;
                    if (t.compare("addplayer") == 0)
                        pointer = 3;
                    if (t.compare("gamestart") == 0)
                        pointer = 4;
                    if (t.compare("replay") == 0)
                        pointer = 0;
                    if (t.compare("quit") == 0)
                        pointer = 6;
                }
                else
                    cout << "the command " << s << " is not in valid state to run.\n";
                index += 1;
            }
            selection = 0;
        }


    }
    cout << "\nexecution finished, thanks for using\n";
    return 0;
}
