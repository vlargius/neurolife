
#include "my_utils.h"
#include "updater.h"

#include "gui_context.h"

Updater::Updater(World & w, Render* render, RC type, const string& ip):
	world(w),
	render(render),
	stepSize(1),
	type(type) {
		client.init(ip);
}

void Updater::setStepSize(int size) {
	stepSize = size;
}

void Updater::run() {
	double dt = 1;
	isActive = true;

	switch (type)
	{
	case RC::NONE:
	{
		break;
	}
	case RC::CLIENT:
	{
		while (!client.connect())
			utils::sleep(300);
		render->run();
		break;
	}
	case RC::SERVER:
	{
		server.run();
		break;
	}
	default:
		break;
	}
	SDL_Event e;

	do {
		Actor& a = world.actors.front();
		if (type != RC::SERVER)
			render->flash();
		
		if (type != RC::CLIENT)
			world.tick(dt);

		if (type == RC::SERVER) {
			string pos = to_string(rand()% 10) + " " + to_string(rand() % 10);//a.getPosComp().serialize();
			server.broadcast(pos);
			server.sync();
		}

		if (type == Updater::RC::CLIENT)
		{
			while (SDL_PollEvent(&e)) {
				//If user closes the window
				if (e.type == SDL_QUIT) {
					isActive = false;
				}
			}
			handleEvent();
			string msg;
			client.receive(msg);
			a.getPosComp().deserialize(msg);
			cout << a.getPosComp().serialize() << endl;
			client.send("ok");
		}

		utils::sleep(stepSize);
	} while (true && isActive);
}


void Updater::handleEvent() {
#ifdef CLI1
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			isActive = false;
		}
	}
#endif
}