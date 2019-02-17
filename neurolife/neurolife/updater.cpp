
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

	switch (type)
	{
	case RC::NONE:
	{
		break;
	}
	case RC::CLIENT:
	{
		client.connect();
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
			string msg;
			client.receive(msg);
			a.getPosComp().deserialize(msg);
			cout << a.getPosComp().serialize() << endl;
			client.send("ok");
		}

		utils::sleep(stepSize);
	} while (true);
}

//
//void World::handle_event() {
//	//while (SDL_PollEvent(&e)) {
//	//	//If user closes the window
//	//	if (e.type == SDL_QUIT) {
//	//		is_active = false;
//	//	}
//	//	//If user presses any key
//	//	if (e.type == SDL_KEYDOWN) {
//	//		switch (e.key.keysym.sym) {
//	//		case SDLK_LEFT:
//	//			context->xs.pos += cam_speed;
//	//			cout << "l";
//	//			break;
//	//		case SDLK_RIGHT:
//	//			context->xs.pos -= cam_speed;
//	//			cout << "r";
//	//			break;
//	//		case SDLK_UP:
//	//			context->ys.pos += cam_speed;
//	//			cout << "u";
//	//			break;
//	//		case SDLK_DOWN:
//	//			context->ys.pos -= cam_speed;
//	//			cout << "d";
//	//			break;
//	//		case SDLK_ESCAPE:
//	//			is_active = false;
//	//		default:
//	//			break;
//	//		}
//	//	}
//	//	if (e.type == SDL_MOUSEWHEEL)
//	//	{
//	//		if (e.wheel.y > 0)
//	//		{
//	//			context->scale() *= scroll_speed;
//	//		}
//	//		else if (e.wheel.y < 0)
//	//		{
//	//			context->scale() /= scroll_speed;
//	//		}
//	//	}
//	//	
//
//	//	
//	//}
//}