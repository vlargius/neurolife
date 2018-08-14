#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

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
	srand(time(NULL));
	string config_name = "default.cfg";

	vector<string> args(argv, argv + argc);
	if (args.size() == 2) {
		config_name = args[1];
	}

	try {
		TTF_Init();
		GUIContext::current_dir = get_font_path(args[0]);
		
		ifstream config_file(config_name.c_str());
		if (!config_file) {
			throw Error("can't find configuration file");
		}

		WorldConfig wcfg;
		config_file >> wcfg; 

		World w;
		GUIContext context(w.get_view(), 1200, 600);
		//ConsoleContext context(cout, w);		
		w.init(wcfg, &context);

		w.start();	
		w.stop();

		TTF_Quit();
	}
	catch (Error& e) {
		cout << e.what() << endl;
	} 
	catch (...) {
		cout << "something bad happened" << endl;
	}

	//wait_key_press();


	return 0;
}