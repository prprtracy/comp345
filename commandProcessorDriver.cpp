#include"fileCommandProcessorAdaptor.cpp"
using namespace std;

int main() {
	int pointer = 0;
	vector<string> engine= {"start","maploaded","map validated","player added","win"};
	commandProcessor cp = commandProcessor();
	fileCommandProcessorAdaptor fcpa = fileCommandProcessorAdaptor("commands.txt");
	cout << "beginning command processor test\n";
	cout << "select one of the following input method:\n";
	cout << "1. input by console\n" << "2. input from a .txt file\n";
	int selection = 0;
	cin >> selection;
	while (selection == 1 || selection == 2||selection==3) {
		if (selection == 1) {
			cout << "Please enter the command:\n";
			cp.getCommand();
			cout << "Please select one of the following choices:\n";
			cout << "1. continue input by console.\n" << "2. input by a .txt file\n" << "3. end of input and start execute\n";
			cin >> selection;
		}
		if (selection == 2) {
			cout << "reading file " << fcpa.fileName << "...\n";
			cp.getFileCommand(fcpa.readCommand());
			cout << "Please select one of the following choices:\n";
			cout << "1. continue input by console.\n" << "2. input by a .txt file\n" << "3. end of input and start execute\n";
			cin >> selection;
		}
		if (selection == 3) {
			int index = 0;
			cout << "start executing the command list\n";
			cout << "simulated game engine start looping\n";
			while (pointer < 5&&index<cp.lis.getList().size()) {
				cout << "current phase: " << engine[pointer]<<"\n";
				cp.execute(engine[pointer],index);
				string s = cp.lis.list[index].getContent();
				if (s.compare("loadmap") == 0)
					pointer = 1;
				if (s.compare("map loaded") == 0)
					pointer = 1;
				if (s.compare("validemap") == 0)
					pointer = 2;
				if (s.compare("addplayer") == 0)
					pointer = 2;
				if (s.compare("gamestart") == 0)
					pointer = 3;
				if (s.compare("replay") == 0)
					pointer = 0;
				if (s.compare("quit") == 0)
					pointer = 5;
			}
			cout << "execution finished, thanks for using";
		}
	}
	return 0;
}