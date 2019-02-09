#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>


using namespace std;

#include "char_render.h"
#include "gui_render.h"
#include "updater.h"
#include "world.h"

#include "exceptions.h"

void wait_key_press() {
	cin.clear();
	cin.ignore();
	int a;
	cin >> a;
}

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	string config_name = "default.cfg";

	vector<string> args(argv, argv + argc);
	if (args.size() == 2) {
		config_name = args[1];
	}

	try {
		ifstream config_file(config_name.c_str());
		if (!config_file) {
			throw Error("can't find configuration file");
			return 0;
		}		

		string ip;

		config_file >> ip;

		WorldConfig wcfg;
		config_file >> wcfg; 

		World world;		
		world.init(wcfg);
		/*CharRender render(&world, cout);*/

		GUIRender render(&world, 800, 600);

		Updater upd(world, &render);
		upd.setStepSize(wcfg.step_size);
		upd.run();
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