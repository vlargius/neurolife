#include <iostream>

#include "world.h"

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

	try {
		w.init(wcfg);
		w.start();
	} catch (...) {
		cout << "something bad happened" << endl;
	}

	w.stop();
	wait_key_press();

	return 0;
}