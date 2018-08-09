#include <iostream>
#include <vector>
#include <fstream>

#include "world.h"
#include "exceptions.h"
#include "my_utils.h"

using namespace std;

void wait_key_press() {
	cin.clear();
	cin.ignore();
	int a;
	cin >> a;
}

int main(int argc, char* argv[]) {
	try {
		string config_name = "default.cfg";

		vector<string> args(argv, argv + argc);
		if(args.size() == 2) {
			config_name = args[1];
		}

		ifstream config_file(config_name.c_str());
		if(!config_file) {
			throw Error("can't find configuration file");
		}

		WorldConfig wcfg;
		config_file >> wcfg; 

		World w;
		
			w.init(wcfg);
			w.start();
	}
	catch (Error& e) {
		cout << e.what() << endl;
	} 
	catch (...) {
		cout << "something bad happened" << endl;
	}

	wait_key_press();


	return 0;
}