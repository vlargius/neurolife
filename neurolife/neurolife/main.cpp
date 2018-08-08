#include <iostream>

#include "world.h"
#include "exceptions.h"

void wait_key_press() {
	cin.clear();
	cin.ignore();
	int a;
	cin >> a;
}

int main() {
	World w;
	WorldConfig wcfg;
	wcfg.actor_count = 1;
	wcfg.feild_cfg= { 10, 10 };
	wcfg.ttl = 100;

	try {
		w.init(wcfg);
		w.start();
	}
	catch (Error& e) {
		cout << e.what();
	} 
	catch (...) {
		cout << "something bad happened" << endl;
	}

	w.stop();
	wait_key_press();

	return 0;
}