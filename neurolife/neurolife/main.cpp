#include <iostream>
#include <vector>
#include <fstream>


#include "world.h"
#include "exceptions.h"
#include "my_utils.h"
#include "draw_context.h"
#include "gui_context.h"

using namespace std;

void wait_key_press() {
	cin.clear();
	cin.ignore();
	int a;
	cin >> a;
}

int main(int argc, char* argv[]) {
	string config_name = "default.cfg";

	vector<string> args(argv, argv + argc);
	if (args.size() == 2) {
		config_name = args[1];
	}

	try {

		ifstream config_file(config_name.c_str());
		if (!config_file) {
			throw Error("can't find configuration file");
		}

		WorldConfig wcfg;
		config_file >> wcfg; 

		World w;
		//GUIContext context(640, 480);
		ConsoleContext context(cout);
		context.init(&w);		
		w.init(wcfg, &context);

		w.start();	
		w.stop();
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