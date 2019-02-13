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
	string config_name = "world.cfg";

	vector<string> args(argv + 1, argv + argc);
	if (args.size() > 0) {
		config_name = args[0];
	}

	string ip = "none";
	if (args.size() > 1) {
		ip = args[1];
	}

	Updater::RC type = Updater::RC::NONE;
	if (ip == "none")
	{
		type = Updater::RC::NONE;
	} else if (ip == "server") {
		type = Updater::RC::SERVER;
	} else
	{
		type = Updater::RC::CLIENT;
	}

	try {
		ifstream config_file(config_name.c_str());
		if (!config_file) {
			throw Error("can't find configuration file");
			return 0;
		}		


		WorldConfig wcfg;
		config_file >> wcfg; 

		World world;		
		world.init(wcfg);
		
		GUIRender render(&world, 800, 600);		

		Updater upd(world, &render, type, ip);	
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