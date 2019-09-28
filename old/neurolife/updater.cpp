
#include "my_utils.h"
#include "updater.h"

#include "gui_context.h"

Updater::Updater(World & w, Render* render, RC type, const string& ip):
	world(w),
	render(render),
	stepSize(1),
	type(type),
	ip (ip) {
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
		client.init(ip);
		client.send("client ready");
		render->run();
		break;
	}
	case RC::SERVER:
	{
		string msg;
		server.recv(msg);
		cout << "recv: " << msg << endl;
		break;
	}
	default:
		break;
	}
	#ifdef CLI
	SDL_Event e;
	#endif

	do {
		Actor& a = world.actors.front();
		if (type != RC::SERVER)
			render->flash();
		
		if (type != RC::CLIENT)
		{
			world.tick(dt);
			cout << "------- TICK --------" << endl;
		}

		if (type == RC::SERVER) {
			string pos = to_string(rand()% 10) + " " + to_string(rand() % 10);//a.getPosComp().serialize();
			server.send(pos);
			//server.sync();
		}

		if (type == Updater::RC::CLIENT)
		{
			#ifdef CLI
			while (SDL_PollEvent(&e)) {
				//If user closes the window
				if (e.type == SDL_QUIT) {
					isActive = false;
				}
			}
			#endif
			string msg;
			client.recv(msg);
			a.getPosComp().deserialize(msg);
			cout << a.getPosComp().serialize() << endl;
			//client.send("ok");
		}

		utils::sleep(stepSize);
	} while (true && isActive);
}

